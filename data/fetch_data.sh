#!/bin/bash

# Define the Github repository URL and the output directory
REPO_URL="https://api.github.com/repos/akielaries/openMTPK-utils/contents/sets"

# Function to download the files
function download_files {
    # Retrieve the list of files in the Github repository
    FILE_LIST=$(curl -s "$REPO_URL" | grep -oE '"download_url": "([^"]+)"' | sed -E 's/"download_url": "(.+)"/\1/g')

    # Loop through each file in the list and download it to the current directory
    for FILE_URL in $FILE_LIST
    do
        FILE_NAME=$(basename "$FILE_URL")
        echo "Downloading $FILE_NAME"
        curl -s -o "$FILE_NAME" "$FILE_URL"
    done
}

# Function to delete the downloaded files
function delete_files {
    # Delete files with .json, .csv, .gz, .data, .dat, and .tsv extensions in the current directory
    find . -maxdepth 1 -type f \( -name "*.json" -o -name "*.csv" -o -name "*.gz" -o -name "*.data" -o -name "*.dat" -o -name "*.tsv" \) -delete
}

# Check if the command-line argument is -del to delete the downloaded files
if [[ $1 == "-del" ]]; then
    echo "Deleting downloaded files..."
    delete_files
else
    echo "Downloading files..."
    download_files
    echo "Done"
fi

