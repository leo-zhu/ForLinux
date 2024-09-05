#!/bin/bash

# Function to display help
show_help() {
    echo "Usage: $0 [--exclude-dir=EXCLUDE_PATH1] [--exclude-dir=EXCLUDE_PATH2] ..."
    echo
    echo "Options:"
    echo "  --exclude-dir=EXCLUDE_PATH    Exclude the specified directory from the search."
    echo "  --help                        Show this help message."
    echo
    echo "This script counts the lines of code in .c, .cpp, .cc, .h, .hh, and .hpp files"
    echo "in the current directory and its subdirectories, with the option to exclude"
    echo "one or more directories from the search."
}

# Initialize exclude arguments as empty
EXCLUDE_ARGS=""

# Parse the arguments to handle --exclude-dir and --help options
for arg in "$@"; do
    case $arg in
        --exclude-dir=*)
            EXCLUDE_PATH="${arg#*=}"
            EXCLUDE_ARGS="$EXCLUDE_ARGS -path $EXCLUDE_PATH -prune -o"
            ;;
        --help)
            show_help
            exit 0
            ;;
        *)
            echo "Invalid argument: $arg"
            echo "Try '$0 --help' for more information."
            exit 1
            ;;
    esac
done

# Find and count lines in all .c, .cpp, .cc, .h, .hh, and .hpp files, excluding specified directories if any
find . $EXCLUDE_ARGS \( -name "*.c" -o -name "*.cpp" -o -name "*.cc" -o -name "*.h" -o -name "*.hh" -o -name "*.hpp" \) -type f -exec wc -l {} +

# To get the total sum of lines across all files (excluding specified paths if any):
total=$(find . $EXCLUDE_ARGS \( -name "*.c" -o -name "*.cpp" -o -name "*.cc" -o -name "*.h" -o -name "*.hh" -o -name "*.hpp" \) -type f -exec cat {} + | wc -l)
echo "Total lines of code (excluding specified directories): $total"

