#include <fstream>
#include <immintrin.h>
#include <iostream>
#include <vector>

struct CSVRecord {
    int id;
    float value;
};

int main() {
    const int chunkSize =
        8; // Number of records to process simultaneously (AVX2)
    const char *filename = "../data/school_scores.csv";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    std::vector<CSVRecord> records;
    records.reserve(chunkSize); // Reserve space for efficient vector growth

    while (!file.eof()) {
        __m256i ids = _mm256_setzero_si256();
        __m256 values = _mm256_setzero_ps();

        for (int i = 0; i < chunkSize; i++) {
            CSVRecord record;
            if (file >> record.id >> record.value) {
                ids = _mm256_insert_epi32(ids, record.id, i);
                values =
                    _mm256_insertf128_ps(values, _mm_set1_ps(record.value), i);
            } else {
                // Handle EOF or invalid data
                break;
            }
        }

        // Store the records in a vector
        for (int i = 0; i < chunkSize; i++) {
            CSVRecord record;
            record.id = _mm256_extract_epi32(ids, i);
            __m128 float4 = _mm256_extractf128_ps(values, i);
            record.value = _mm_cvtss_f32(float4);
            records.push_back(record);
        }
    }

    // Print the data from the 'records' vector
    for (const CSVRecord &record : records) {
        std::cout << "ID: " << record.id << ", Value: " << record.value
                  << std::endl;
    }

    file.close();
    return 0;
}
