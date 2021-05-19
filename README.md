![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/Anthony-T-N/Smart_Scan_Pattern_Extractor-URL_Builder)
![C++](https://img.shields.io/badge/Language-C%2B%2B-ff69b4)
![version](https://img.shields.io/badge/version-1.0.0-yellow.svg)
![support](https://img.shields.io/badge/OS-Windows-orange.svg)

# Smart_Scan_Pattern_Extractor-URL_Builder

[Draft]

Overview
-
A console application used to assist with constructing URLs that are used to download "Smart Scan Patterns" from Trend Micro.
Manually updating and applying "Smart Scan Patterns" from Trend Micro to physically isolated systems/servers remains a tedious and repetitive task. This console application aims to reduce headaches by automating the manual steps 1 to 10 as outlined at the following [link](https://success.trendmicro.com/solution/000243463-Performing-a-manual-pattern-update-for-an-OfficeScan-Apex-One-server).

How It Works
-
Version 1

- Reads from "toread.txt" text file containing the "smart pattern scan" section from the downloaded server.ini file.
- Processes text from the file line by line.
- Extracts the neccessary details from the lines and combines it with other details to create proper URLs.
- Outputs newly created and usable URLs to a new text file called "output.txt", allowing users to immediately begin downloading the smart patterns.

Version 2



Usage Overview
-
Version 1


Version 2
