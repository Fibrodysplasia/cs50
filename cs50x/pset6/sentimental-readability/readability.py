import re

counts = {
    'letters': 0,
    'words': 0,
    'sentences': 0
}

def update_counts(text):
    counts['letters'] = len(re.sub(r'[^a-zA-Z]', '', text))
    counts['words'] = len(re.split(r'\s', text))
    counts['sentences'] = len(re.split(r'[.!?]', text)) - 1

def get_readability_index(counts):
    L = counts['letters'] / (counts['words'] / 100)
    S = counts['sentences'] / (counts['words'] / 100)
    return round(0.0588 * L - 0.296 * S - 15.8)

def main():
    text = input('Text: ')
    update_counts(text)
    index = get_readability_index(counts)
    if index < 1:
        print('Before Grade 1')
    elif index >= 16:
        print('Grade 16+')
    else:
        print(f'Grade {index}')

if __name__ == '__main__':
    main()