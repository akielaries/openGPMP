#include "utility.h"
#include "hash_table_data_structure.h"


int main()
{
	printf("\n\nSTART: %s\n", __func__);
	int process_data, max_row_size, index, row_size, total_rows;
    FILE *input_stream, *output_stream;
	char current_case;
	max_row_size = 1;
	// Calculating max_rows_size
	for(int current_data_file = 0; current_data_file < 3; current_data_file++)
	{
		// Opening data stream
		input_stream = fopen(data_file[current_data_file], "r");
		// Calculating Stats
		data_stats(input_stream, &row_size, &total_rows);
		// Closing data stream
		fclose(input_stream);
		if(max_row_size < row_size)
		{
			max_row_size = (row_size+1);
		}
	}
	
	char current_key[max_row_size];
	void* hash_back;
	void* current_hash;
	int current_table_length;
	printf("row_size: %d\n", max_row_size);

		
		
		printf("\n%s: Which case you want to run?", __func__);
		printf("(1, 2, 3): \t", __func__);
		scanf("%c", &current_case);
		// printf("\ncur_case:%d\n", current_case);
		
			switch(current_case)
			{
				case '1':
					printf("CASE 1 IS ACTIVE");
					// Opening data stream to calculate stats
					// Note: 48 is a ascii value for 0, "thus -49 will produce correct index
					input_stream = fopen(data_file[current_case-49], "r");
					// Calculating Stats
					data_stats(input_stream, &row_size, &total_rows);
					// Closing data stream
					fclose(input_stream);
					
					// No reason to do this line :D
					process_data = total_rows;
					// Check if hash_table is created
					hash_table* case_one_hash_table = hash_table_create();
					if (case_one_hash_table == NULL)
					{
						out_of_memory();
					}
						
					// Opening data stream to read in data
					input_stream = fopen(data_file[current_case-49], "r");
					printf("%s: Iterating over rows:\n", __func__);
					for (int iterator = 0; iterator < process_data; iterator++)
					{
						// Displaying current row
						printf("\t%s: Current row is: %d\n", __func__, (iterator+1));

						// Read in key
						fgets(current_key,max_row_size,input_stream);
						// Removing end of line char from key
						current_key[strcspn(current_key, "\r\n")] = 0;
						// Displaying current key
						printf("\t%s: Current key is: %s\n", __func__, current_key);
							
						// Calculating hash
						current_hash = key_to_hash(current_key);
						// Displaying current hash
						printf("\t%s: Current hash is: %p\n", __func__, current_hash);
								
						// Setting current key hash pair into hash table
						hash_table_set(case_one_hash_table, current_key, current_hash);
							
						// Checking if current key is in hash table
						hash_back = hash_table_get(case_one_hash_table, current_key);
						if(hash_back != NULL)
						{
							printf("\t%s: We managed to get hash back: %p\n", __func__, hash_back);
						}
						else
						{
							printf("\t%s: We could not get hash back: %p\n", __func__, hash_back);
						}
						
						// Checking current table length
						current_table_length = hash_table_length(case_one_hash_table);
						printf("\t%s:Table length: %d\n", __func__, current_table_length);
							
						
					}

					// Closing data stream
					fclose(input_stream);
					hash_table_destroy(case_one_hash_table);
					printf("DONE: %s\n", __func__);
												
					
					break;

				case '2':
					printf("CASE 2 IS ACTIVE");
					// Opening data stream to calculate stats
					input_stream = fopen(data_file[current_case-49], "r");
					// Calculating Stats
					data_stats(input_stream, &row_size, &total_rows);
					// Closing data stream
					fclose(input_stream);
					
					// This line again :D
					process_data = total_rows;
					// Check if hash_table is created
					hash_table* case_two_hash_table = hash_table_create();
					if (case_two_hash_table == NULL)
					{
						out_of_memory();
					}
						
					// Opening data stream to read in data
					input_stream = fopen(data_file[current_case-49], "r");
					printf("%s: Iterating over rows:\n", __func__);
					for (int iterator = 0; iterator < process_data; iterator++)
					{
						// Displaying current row
						printf("\t%s: Current row is: %d\n", __func__, (iterator + 1));

						// Read in key
						fgets(current_key,max_row_size,input_stream);
						// Removing end of line char from key
						current_key[strcspn(current_key, "\r\n")] = 0;
						// Displaying current key
						printf("\t%s: Current key is: %s\n", __func__, current_key);
							
						// Calculating hash
						current_hash = key_to_hash(current_key);
						// Displaying current hash
						printf("\t%s: Current hash is: %p\n", __func__, current_hash);
								
						// Setting current key hash pair into hash table
						hash_table_set(case_two_hash_table, current_key, current_hash);
							
						// Checking current table length
						current_table_length = hash_table_length(case_two_hash_table);
						printf("\t%s:Table length: %d\n", __func__, current_table_length);
							
						
					}

					// Closing data stream
					fclose(input_stream);
					hash_table_destroy(case_two_hash_table);
					printf("DONE: %s\n", __func__);
												
		
					
					
					
					
					break;

				case '3':
					printf("CASE 3 IS ACTIVE");
					// Opening data stream to calculate stats
					input_stream = fopen(data_file[current_case-49], "r");
					// Calculating Stats
					data_stats(input_stream, &row_size, &total_rows);
					// Closing data stream
					fclose(input_stream);
					
					// Prompt for number of data to include in hash table
					printf("\n%s: Enter the number between 1 and ", __func__);
					printf("%d to read data into the Hash table: ",total_rows);
					// Look this time we do use process_data!
					scanf("%d", &process_data);fflush(stdin);
					printf("%s: You choose to process: %d rows of data\n\n", __func__, process_data);
					if(process_data >= 1 && process_data <= total_rows)
					{
						// Check if hash_table is created
						hash_table* case_three_hash_table = hash_table_create();
						if (case_three_hash_table == NULL)
						{
							out_of_memory();
						}
							
						// Opening data stream to read in data
						input_stream = fopen(data_file[current_case-49], "r");
						printf("%s: Iterating over rows:\n", __func__);
						for (int iterator = 0; iterator < process_data; iterator++)
						{
							// Displaying current row
							// printf("\t%s: Current row is: %d\n", __func__, (iterator + 1));

							// Read in key
							fgets(current_key,max_row_size,input_stream);
							// Removing end of line char from key
							current_key[strcspn(current_key, "\r\n")] = 0;
							// Displaying current key
							// printf("\t%s: Current key is: %s\n", __func__, current_key);
								
							// Calculating hash
							current_hash = key_to_hash(current_key);
							// Displaying current hash
							// printf("\t%s: Current hash is: %d\n", __func__, current_hash);
									
							// Setting current key hash pair into hash table
							hash_table_set(case_three_hash_table, current_key, current_hash);
								

							// Checking current table length
							current_table_length = hash_table_length(case_three_hash_table);
							printf("\t%s:Table length: %d\n", __func__, current_table_length);
								
							
						}

						// Closing data stream
						fclose(input_stream);
						hash_table_destroy(case_three_hash_table);
						printf("DONE: %s\n", __func__);
					}
					else
					{
						printf("%s: ERROR: ", __func__);
						printf("Makse sure to enter numbers between %d and %d. ", 1, total_rows);
						printf("If error persists check data file\n");
						printf("EXITING ON ERROR FROM: %s | ON LINE: %d\n", __func__,__LINE__);
					}						

					break;

				case '4':
					printf("CASE 4 IS ACTIVE");
                    // Opening data stream to calculate stats
                    input_stream = fopen(data_file[current_case-49], "r");
                    // Calculating Stats
                    data_stats(input_stream, &row_size, &total_rows);
                    // Closing data stream
                    fclose(input_stream);

                    // Prompt for number of data to include in hash table
                    printf("\n%s: Enter the number between 1 and ", __func__);
                    printf("%d to read data into the Hash table: ",total_rows);
                    // Look this time we do use process_data!
                    scanf("%d", &process_data);fflush(stdin);
                    printf("%s: You choose to process: %d rows of data\n\n", __func__, process_data);
                    if(process_data >= 1 && process_data <= total_rows)
                    {
                        // Check if hash_table is created
                        hash_table* case_three_hash_table = hash_table_create();
                        if (case_three_hash_table == NULL)
                        {
                            out_of_memory();
                        }

                        // Opening data stream to read in data
                        input_stream = fopen(data_file[current_case-49], "r");
                        printf("%s: Iterating over rows:\n", __func__);
                        for (int iterator = 0; iterator < process_data; iterator++)
                        {
                            // Displaying current row
                            // printf("\t%s: Current row is: %d\n", __func__, (iterator + 1));

                            // Read in key
                            fgets(current_key,max_row_size,input_stream);
                            // Removing end of line char from key
                            current_key[strcspn(current_key, "\r\n")] = 0;
                            // Displaying current key
                            // printf("\t%s: Current key is: %s\n", __func__, current_key);

                            // Calculating hash
                            current_hash = key_to_hash(current_key);
                            // Displaying current hash
                            // printf("\t%s: Current hash is: %d\n", __func__, current_hash);

                            // Setting current key hash pair into hash table
                            hash_table_set(case_three_hash_table, current_key, current_hash);


                            // Checking current table length
                            current_table_length = hash_table_length(case_three_hash_table);
                            printf("\t%s:Table length: %d\n", __func__, current_table_length);


                        }

                        // Closing data stream
                        fclose(input_stream);
                        hash_table_destroy(case_three_hash_table);
                        printf("DONE: %s\n", __func__);
                    }
                    else
                    {
                        printf("%s: ERROR: ", __func__);
                        printf("Makse sure to enter numbers between %d and %d. ", 1, total_rows);
                        printf("If error persists check data file\n");
                        printf("EXITING ON ERROR FROM: %s | ON LINE: %d\n", __func__,__LINE__);
                    }
					//case_4();
					break;

				default:
					printf("ERROR! NO SUCH CASE");
				
			}

		
	
	
	// Output Hash
	// open output file

	

	return 0;
}



