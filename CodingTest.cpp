
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class UniqueWords
{

public:
   
   //VeteAlaMrd();
   //~VeteAlaMrd();

   void FindWordOccurrences(string text);
   void SentencesInFile(string text);
   void WordsInSentence();
   void UpdateWordOccurrences(string word);
   void UpdateWordSentenceApp(string word, int sentenceNum);
   void PrintData();

private:
   
   map<string, int>           m_wordOccurrences;
   map<string, vector<int> >  m_wordSentenceApp;

   vector<string>             m_sentences;
};

void UniqueWords::FindWordOccurrences(string text)
{
   //Store sentences in file
   SentencesInFile(text);
   //Split words and find needed data
   WordsInSentence();
}

void UniqueWords::SentencesInFile(string text)
{
   string delimiter = ".";
   int pos = 0;
   int start = 0;
   int end = 0;

   while ((pos = text.find(delimiter, start)) != string::npos)
   {
      end = (pos + 1) - start;
      m_sentences.push_back(text.substr(start, end));
      start = pos + 2;
   }
}

void UniqueWords::WordsInSentence()
{
   string delimiter = " ";
   string delim = ".";
   string uniqueWord;
   
   for (int i = 0; i < m_sentences.size(); i++) 
   {
      int pos = 0;
      int start = 0;
      int end = 0;
      while ((pos = m_sentences[i].find(delimiter, start)) != string::npos ||
             (pos = m_sentences[i].find(delim, start)) != string::npos)
      {               
         end = pos - start;
         uniqueWord = m_sentences[i].substr(start, end);
         transform(uniqueWord.begin(), uniqueWord.end(), uniqueWord.begin(), ::tolower);
         UpdateWordOccurrences(uniqueWord);
         UpdateWordSentenceApp(uniqueWord, i+1);
         start = pos + 1;
      }
   }
}

void UniqueWords::UpdateWordOccurrences(string word)
{
   bool wordFoundInLine = false;

   map<string, int>::iterator itr;

   itr = m_wordOccurrences.find(word);

   if (itr != m_wordOccurrences.end())
   {
      itr->second++;
   }
   else
   {
      m_wordOccurrences.insert(pair<string, int>(word, 1));
   }
}

void UniqueWords::UpdateWordSentenceApp(string word, int sentenceNum)
{
   vector<int> sentences;
   map<string, vector<int> >::iterator itr;

   itr = m_wordSentenceApp.find(word);

   if (itr != m_wordSentenceApp.end())
   {
      vector<int> wordSentence(itr->second);
      if (find(wordSentence.begin(), wordSentence.end(), sentenceNum) == wordSentence.end())
      {
         itr->second.push_back(sentenceNum);
      }
   }
   else
   {
      sentences.push_back(sentenceNum);
      m_wordSentenceApp.insert(pair<string, vector<int> >(word, sentences));
   }
}

void UniqueWords::PrintData()
{
   map<string, int>::iterator itr1;
   map<string, vector<int> >::iterator itr2 = m_wordSentenceApp.begin();

   for (itr1 = m_wordOccurrences.begin(); itr1 != m_wordOccurrences.end(); ++itr1)
   {
      cout << std::left << std::setw(12) << itr1->first
      << ": Occurrences: " << itr1->second << "; Sentences: [";      

      for (int i = 0; i < itr2->second.size(); i++)
      {
         cout << itr2->second[i];
         if (i+1 == itr2->second.size())
         {
            cout << "]\n";
         }
         else
         {
            cout << ", ";
         }
      }
      ++itr2;
   }
}

int main () 
{  
   UniqueWords uniqueWords;
   string strText;
   int    lineNum;

   ifstream myfile("CodingTest.txt", ios::in);

   if (myfile.is_open())
   {
      while (getline(myfile, strText))
      {
         uniqueWords.FindWordOccurrences(strText);
         lineNum++;
         break;
      }
      myfile.close();
   }
   else
   {
      cout << "Unable to open file\n"; 
   }

   uniqueWords.PrintData();

   return 0;
}

