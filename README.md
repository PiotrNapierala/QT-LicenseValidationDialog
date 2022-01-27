# QT-LicenseValidationDialog

## Basic
LicenseValidationDialog is a class designed to validate license keys on the user's side. The class is designed to verify the correctness of the license key of the software you create. To use the program you created, the user will have to provide:<br>
- License key<br>
- License hash<br>
- User name<br>
- Expiration date<br><br>
![general_look](https://user-images.githubusercontent.com/72657389/151381678-26ea7cb3-89f1-4c74-8bb6-44b14c84fc92.png)<br>

## Errors
If the provided data is incorrect or the fields are empty, an appropriate message will appear.<br>
![data_error](https://user-images.githubusercontent.com/72657389/151381839-6d231168-b21d-4bf9-94f7-bf25f0634068.png)<br><br>

The class for verifying the remaining license validity time connects to an external NTP time server. If the connection fails, an appropriate message will be displayed.<br>
![time_error](https://user-images.githubusercontent.com/72657389/151382139-d420c093-1be1-4077-b463-3d5e30a65e25.png)<br><br>

If the license expires, an appropriate message will be displayed.<br>
![timeleft_error](https://user-images.githubusercontent.com/72657389/151382267-e564d66b-b1d0-40a0-8cdf-e62e5161f102.png)<br><br>

If all data is correct and the license is valid, the class will return the value true in the public variable - valid.

## How to use?
To use the class, you need to add the LicenseValidationDialog class files to your project. Just copy the files to your project directory and make changes to your application's .pro file by adding the files one by one after the '\\' character. The next step is to add the IMG directory to your project folder. There are basic icons inside. Change them as you see fit, but be sure not to rename the files.<br>
![file_adding](https://user-images.githubusercontent.com/72657389/151382645-20061773-9d69-4dff-bac5-a4d99b243702.png)<br><br>

Okay, we are half the battle. Now, you need to make some changes to the main.cpp file. First, we create an object named m, it can be named whatever you want, but let's follow this nomenclature. Then we check it, if we have already entered the license and if it is a valid CheckBasicValid() function. The function gets information from the save file (more info will be provided later). If the function returns false, then either we do not have the save file or something is wrong with the license. Therefore, we run the validation window - m.exec(). Now, we have three options: the license was checked automatically, the user closed the validation window or entered the correct data. It doesn't matter, the result of these operations is saving the license information in the valid variable. Now, we have to check if the valid variable is equal to be true. If so, we start the main application window, if not - close the application. Below is an example of use:<br>
![main cpp](https://user-images.githubusercontent.com/72657389/151383273-9c6fe5c1-8e6c-4c16-9fd6-270d027dcab0.png)<br><br>

Oh, and don't forget to include class!<br>
![include](https://user-images.githubusercontent.com/72657389/151383424-83904a6b-66ce-4f47-b72c-5a68a66f49d9.png)<br><br>

## Settings
You will find them in the header file.<br>
![settings](https://user-images.githubusercontent.com/72657389/151383567-57d76d20-fdf0-423d-bf88-8f663aa89357.png)<br>
The given api key values are examples, be sure to change them!<br><br>

- API_KEY - Your unique API key. It should be at least 20 characters long. It is used to create and verify user licenses. It should be located only here and should not be scattered around. It's connected with the security of your application! After compiling the application to an .exe file, it will be in a binary form - impossible to read. But remember, it's still in the source code, be careful what you share!
- NTP_SERVER - Time server, choose your own server. I live in Poland, that's why I used a Polish time server - tempus1.gum.gov.pl
- save_license - The variable that stores information whether, after correct validation, the application is to save the license data in the license file. true - save, false - do not save. If the data is not saved, the user will have to enter them each time the application is started. Despite the information being saved, the application will check the license validity anyway by connecting to the time server.
- set_custom_language - Whether the class should use a language other than the default - English. If so, the application will look for the language file in the default location (application exe folder / language.txt) unless a different path is specified in the custom_language_file_path variable.

## Language file
Each name should be put on a new line.
Structure of the language file:
- Title of the validation window
- License key label
- License hash label
- User Name label
- Expiration date label
- Cancel button text
- OKAY button text
- Error window title
- Expiration error
- NTP connection error
- Invalid data error

Sample file:<br>
![language_file](https://user-images.githubusercontent.com/72657389/151384121-2f072c04-3670-4690-92f0-74620cdf761b.png)<br>
The file should contain strictly 11 lines!

## How does the class work?
In the beginning, the developer generates any license key. You can use free online license key generators. So you already have a generated license, you also come up with a username and expiry date of the license. What about the hash? And here is all the magic. The hash is generated from the license key, username, license expiration date and your API key. After generating the hash, we share the data with the user. The class does exactly the same, generates a hash based on the given data (license key, username and license expiration date) and compares it with the hash provided by the user. If the hashes are correct, the data is correct. But what if the user changes the data himself, for example extends the license validity by changing the license expiry date? This is what an API key only you know is for. The user does not know the API key and therefore cannot generate the hash corresponding to the new license data. You are safe until someone knows your API key. Protect it at all costs!

## How can I generate license keys and the corresponding hashes?
The formula is simple:<br>
In the beginning, we create one string of individual elements in the order: license_key + user_name + expiration_date (format: dd.MM.yyyy) + API_KEY. Then we generate a hash from this string using the Sha256 method. You can easily do it with sha256 generators online. The result of this is our hash that we provide to the user along with the username, license key and license expiry date. That's all!<br><br>

PS Easier license generation will be possible later with my generator. Search for the repository later - LicenseValidationGenerator. If it is not there yet, I am still working on it.

## Something else?
If you use my class, please leave a message about it somewhere in your application. I will be extremely happy and motivated to continue working!
