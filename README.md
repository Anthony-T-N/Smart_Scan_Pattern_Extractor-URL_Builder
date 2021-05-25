![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/Anthony-T-N/Smart_Scan_Pattern_Extractor-URL_Builder)
![C++](https://img.shields.io/badge/Language-C%2B%2B-ff69b4)
![version](https://img.shields.io/badge/version-2.0.0-yellow.svg)
![support](https://img.shields.io/badge/OS-Windows-orange.svg)

# Smart_Scan_Pattern_Extractor-URL_Builder

[Draft]

Overview
-
A console application to assist users with constructing URLs that are used to download "Smart Scan Patterns" files from Trend Micro and applied to a Apex One server.
Manually updating and applying "Smart Scan Patterns" from Trend Micro to physically isolated systems/servers remains a tedious and repetitive task. This console application aims to reduce that painful process by automating the manual steps 1 to 10 as outlined at the following [link](https://success.trendmicro.com/solution/000243463-Performing-a-manual-pattern-update-for-an-OfficeScan-Apex-One-server).

How It Works
-
Version 1

- Reads from "toread.txt" text file containing the "Smart Scan Patterns" section from the downloaded server.ini file.
- Processes text from the file line by line.
- Extracts the neccessary details from the lines and combines it with other details to create proper URLs.
- Outputs newly created and usable URLs to a new text file called "output.txt", allowing users to immediately begin downloading the smart patterns.

Version 2

- Employs [CURL](https://curl.se/) to download a temporary copy of "server.ini" called "temp.ini". 
- A copy of "temp.ini" is made with the [Server] section commented out as instructed on step 10 in Trend Micro's [instructions](https://success.trendmicro.com/solution/000243463-Performing-a-manual-pattern-update-for-an-OfficeScan-Apex-One-server).
- Creates the directory location and folders. Renames root folder with current date.

Usage Overview
-

Version 1

1) Create a new text file named "toread.txt". 
2) Navigate to Trend Micro's official URL to open up the "server.ini" file and copy the section of text with lines that all contain "icrc".
3) Paste the copied section to "toread.txt" and save/close the file.
4) Run the Smart_Scan_Pattern_Extractor-URL_Builder executable.

Version 2

Nil (Automated)
Simply execute the application.
