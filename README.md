![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/Anthony-T-N/Smart_Scan_Pattern_Extractor-URL_Builder)
![C++](https://img.shields.io/badge/Language-C%2B%2B-ff69b4)
![version](https://img.shields.io/badge/version-2.0.0-yellow.svg)
![support](https://img.shields.io/badge/OS-Windows-orange.svg)

# Smart_Scan_Pattern_Extractor-URL_Builder

Overview
-
A console application to assist system administrators and ICT/security engineers with constructing URLs which are used to download "Smart Scan Patterns" files from Trend Micro and to be applied to a Apex One server(s).
Manually updating and applying "Smart Scan Patterns" from Trend Micro to physically isolated systems/servers remains a tedious and repetitive task. This console application aims to reduce that painful process by automating the manual steps 1 to 10 as outlined in the following [instructions](https://success.trendmicro.com/solution/000243463-Performing-a-manual-pattern-update-for-an-OfficeScan-Apex-One-server) (Using article last updated from 9 Apr 2021).

How It Works
-
**Version 1**

- Performs a file validation check for any text files named "toread.txt".
- Reads from "toread.txt" text file containing the "Smart Scan Patterns" section from the downloaded server.ini file.
- Processes text from the file line by line.
- Extracts the necessary details from the lines and combines it with other details to create proper URLs.
- Outputs newly created and usable URLs to a new text file called "output.txt", allowing users to immediately begin downloading the smart patterns.

**Version 2**

- Employs [CURL](https://curl.se/) to download a temporary copy of "server.ini" called "temp.ini". 
- A copy of "temp.ini" is created with the [Server] section commented out as instructed on step 10 in Trend Micro's [instructions](https://success.trendmicro.com/solution/000243463-Performing-a-manual-pattern-update-for-an-OfficeScan-Apex-One-server).
- Creates the necessary folders and renames root folder with current date (YYYY-MM-DD). Example of directory structure:
YYYY-MM-DD\update\pattern\icrc
- Reads every line of the "temp.ini" file to identify line containing "[Server]". All lines below (until empty space) are commented out (";" added before all lines). New file containing commented out lines outputted as "server.ini" and stored at YYYY-MM-DD\update, with the previous file "temp.ini" removed.
- Console application will then read through every line of the "server.ini" file to identify for any lines containing the phrase "icrc".
- Once  identified, the line is captured as a string and spliced accordingly. Example:
1) -> P.48020000.Merge.1= | **pattern/icrc/ioth_1674300.1674500** | ,1674300,2063
2) -> http://osce14-p.activeupdate.trendmicro.com/activeupdate/ + pattern/icrc/ioth_1674300.1674500
- Once a formal URL has been created. [CURL](https://curl.se/) is used again to access the URLs individually and stores the newly downloaded files (with appropriate names) at YYYY-MM-DD\update\pattern\icrc.
- The URL is then modified where the extension is replaced with the "sig" extension to download the signature files of the previous downloaded files:
1) -> http://osce14-p.activeupdate.trendmicro.com/activeupdate/pattern/icrc/ + ioth_1674300.~~1674500~~
2) -> http://osce14-p.activeupdate.trendmicro.com/activeupdate/pattern/icrc/ + ioth_1674300.**sig**
- These newly formed URLs are also downloaded to the same directory.

Usage Overview
-
**Version 1**

1) Manually create a new text file named "toread.txt" and ensure it is located in the same folder directory as the executable.
2) Navigate to Trend Micro's official URL to open up the "server.ini" file and copy the section of text with lines that all contain "icrc".
3) Paste the copied section to "toread.txt" and save/close the file.
4) Run the Smart_Scan_Pattern_Extractor-URL_Builder executable.

**Version 2**

Nil (Automated). Simply execute the application.
