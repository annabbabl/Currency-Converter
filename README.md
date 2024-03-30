# Currency Converter

This is a C++ Currency Converter application. It enables users to convert from one currency to another of their choosing. Additionally, the application provides historical data of the initial currency for context and deeper financial analysis.
![Currency Converter Icon](./icon.png)

## Installation

To get started with the Currency Converter, follow the installation instructions for your specific operating system.

First, clone the repository to your local machine using the following command in your terminal:

```bash
git clone <repository-url>
```

To build and run the project you should have Qt framework and curl library installed.
Make sure that you have inserted your own path to curl library and that you have added qt directory to window's PATH variable. 
Then you should create directory (debug for example) and go into it. After that use "cmake ..". It will generate makefiles for this project.
You can specify which makefiles are will be generated. If you use MinGW g++ compiler then you can use this command: cmake .. -G "MinGW Makefiles". Make sure that all necessary libraries are in there (Qt dll's and libcurl-x64.dll).


# Windows

```bash chmod +x windowsStartScript.sh
./windowsStartScript.sh
```


# MacOS

```bash chmod +x macOsStartScript.sh
./macOsStartScript.sh
```

Now start exchanging money!
