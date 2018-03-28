#!/usr/bin/python
#Ryan Miyahara
#UCID: 804585999

"""
Implement the "comm" command from Linux into python.

Take 2 files as input.
Left column (1) prints words unique to file1.
Middle column (2) prints words unique to file2.
Right column (3) prints words in both file1 and file2.
"-u flag" allows a nonsorted file to be inputted.
"-1" "-2" "-3" flag, or any combination, removes the respective column.
SORT, APPLY FLAGS, THEN PRINT
APPLY FLAGS IN DESCENDING ORDER
"""

import sys
import argparse

class Comm:
    def __init__(self, filename1, filename2):
        if (filename1 == "-" and filename2 == "-"):
            print ("Error: Both inputs cannot be STDIN")
        elif (filename1 == "-"):
            f1 = sys.stdin
            f2 = open(filename2, 'r')
        elif (filename2 == "-"):
            f1 = open(filename1, 'r')
            f2 = sys.stdin
        else:
            f1 = open(filename1, 'r')
            f2 = open(filename2, 'r')

        self.first = f1.readlines()
        self.second = f2.readlines()
        self.first = [i.strip() for i in self.first]
        self.second = [j.strip() for j in self.second]
        f1.close()
        f2.close()
        self.final = []

    def sort(self):
        first_counter = 0
        second_counter = 0
        while (True):
            if (first_counter >= len(self.first) and second_counter >= len(self.second)):
                #Both files have reached the end.
                break
            elif (first_counter >= len(self.first)):
                #Fill the rest with second.
                for i in range(second_counter, len(self.second)):
                    self.final.append("\t" + self.second[i])
                    #One tab character for second column.
                break
            elif (second_counter >= len(self.second)):
                #Fill the rest with first
                for i in range(first_counter, len(self.first)):
                    self.final.append(self.first[i])
                    #No tab character for first colmn.
                break

            if (self.first[first_counter] == self.second[second_counter]):
                #A match is found
                self.final.append("\t\t" + self.first[first_counter])
                #2 tabs for 3rd column
                first_counter += 1
                second_counter += 1
            elif (self.first[first_counter] < self.second[second_counter]):
                #First is lexicographically before second
                self.final.append(self.first[first_counter])
                #No tabs for first column
                first_counter += 1
            elif (self.first[first_counter] > self.second[second_counter]):
                #Second is lexicographically before the first
                self.final.append("\t" + self.second[second_counter])
                #1 tab for second column
                second_counter += 1
            else:
                print ("Error: something went wrong in the sort function.")

    def sortu(self):
        second_ignore = [] #0 if match not found, 1 if so
        for i in range(0, len(self.second)):
            second_ignore.append(0)
        for i in self.first:
            added = False
            for j in range(0, len(self.second)):
                if (i == self.second[j] and second_ignore[j] == 0):
                    second_ignore[j] = 1
                    self.final.append("\t\t" + i)
                    added = True
                    break
            if (not added):
                self.final.append(i)
        for i in range(0, len(self.second)):
            if (second_ignore[i] == 0):
                self.final.append("\t" + self.second[i])


    def flag1(self):
            i = 0
            while (i < len(self.final)):
                if (not self.final[i].startswith('\t')):
                    del self.final[i]
                else:
                    i += 1
            for i in range(0, len(self.final)):
                #Fix rows after first is deleted
                if (self.final[i].startswith('\t\t')):
                    self.final[i] = self.final[i].strip()
                    self.final[i] = '\t' + self.final[i]
                else:
                    self.final[i] = self.final[i].strip()

    def flag2(self):
        i = 0
        while (i < len(self.final)):
            if (self.final[i].startswith('\t') and not (self.final[i].startswith('\t\t'))):
                del self.final[i]
            else:
                i += 1
        for i in range(0, len(self.final)):
            #Fix rows after second is deleted
            if (self.final[i].startswith('\t\t')):
                self.final[i] = self.final[i].strip()
                self.final[i] = '\t' + self.final[i]

    def flag3(self):
        i = 0
        while (i < len(self.final)):
            if self.final[i].startswith('\t\t'):
                del self.final[i]
            else:
                i += 1

    def finalprint(self):
        didprint = False
        for i in self.final:
            print (i)
            didprint = True
        if (didprint):
            print ("")

def main():
    parser = argparse.ArgumentParser(prog='comm', description="The comm utility\
     shall read file1 and file2, which should be ordered in the current collati\
     ng sequence, and produce three text columns as output: lines only in file1\
     , lines only in file2, and lines in both files.")
    parser.add_argument('file1', help = 'File 1 of comm')
    parser.add_argument('file2', help = 'File 2 of comm')
    parser.add_argument('-1', '--flag1', action = "store_true", default =
    False, help = "Hide column 1, unique to FILE1.")
    parser.add_argument('-2', '--flag2', action = "store_true", default =
    False, help = "Hide column 2, unique to FILE2.")
    parser.add_argument('-3', '--flag3', action = "store_true", default =
    False, help = "Hide column 3, shared between FILE1 and FILE2.")
    parser.add_argument('-u', '--unsorted', action = "store_true", default =
    False, help = "Allows unsorted files to be used.")
    args = parser.parse_args()

    if (len(sys.argv) > 4):
        parser.error("wrong number of operands")

    a = Comm(args.file1, args.file2)
    if (args.unsorted):
        a.sortu()
    else:
        a.sort()
    if (args.flag3):
        a.flag3()
    if (args.flag2):
        a.flag2()
    if (args.flag1):
        a.flag1()
    a.finalprint()

if __name__ == "__main__":
    main()
