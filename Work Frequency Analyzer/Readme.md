# WordFrequencyAnalyzer (C++ Exercise)

This program analyzes a large text file to count the occurrences of user-specified words and displays a bar graph showing their frequency. It also saves the output to a separate file.

---

## Instructions

1. The program asks the user for:  
   - Input text file name  
   - File containing the search words  
   - Output file name  

2. The program terminates with an error message if any file cannot be opened.  

3. Word definition:  
   - A word is a sequence of **non-whitespace characters** containing more than one letter.  
   - Punctuation at the beginning or end of a word is removed.  
   - Punctuation inside a word and digits are considered part of the word.  
   - All input is converted to **lowercase**.  

4. Use the `ispunct` function (from `cctype`) to detect punctuation.  

---

## Implementation

- **Class:** `ReadWords`  
  - Manages reading and storing words from the text file.  
  - Overloads the `<<` operator to automatically output word counts and bar graphs.  

- **Function:** `generateBarGraph`  
  - Produces a bar graph with word counts and percentages.  
  - Outputs to both `cout` and the specified output file.  

- Recommended approach:  
  - Read the list of words into an array of strings before processing the text file.  

---


