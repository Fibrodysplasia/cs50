import csv
import sys

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run

def check_if_match(person, unknown_person):
    for key in person:
        if int(person[key]) != int(unknown_person[key]):
            return False
    return True
            

def main(db_file, sequence_file):
        
    unknown_person = {}

    # TODO: Read database file into a variable
    with open(db_file, 'r', newline='') as file:
        reader = csv.reader(file)
        fieldnames = next(reader)
        data = [dict(zip(fieldnames, row)) for row in reader]
    
    # TODO: Read DNA sequence file into a variable
    sequence = open(sequence_file, 'r').read()

    # TODO: Find longest match of each STR in DNA sequence
    for key in data[1]:
        if key != 'name':
            unknown_person[key] = longest_match(sequence, key)
            

    # TODO: Check database for matching profiles
    for person in data:
        person_name = person['name']
        person.pop('name')
        if check_if_match(person, unknown_person):
            print(person_name)
            sys.exit(0)
    print('No match')

if __name__ == "__main__":
        # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print('Usage: python3 dna.py data.csv sequence.txt')
        sys.exit(1)
        
    db_file = sys.argv[1]
    sequence_file = sys.argv[2]

    main(db_file, sequence_file)
