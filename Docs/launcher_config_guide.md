Here is a complete guide on how to customise the launcher.

## 1. Find the "launcher_config.txt" file
   This is where you will be able to customise it
   
   **Windows**: Should be in the same folder as the launcher
   
   **MacOS / Linux**: Should be in `~/.dsda-doom`

## 2. Structure of this file
   
   It is divided in 3 parts
   
   1 - Toggles
   
   2 - Bottom row type
   
   3 - Bottom row boxes
   
## 3. Customise the Toggles
   
   ![Screenshot 2021-09-09 at 19 06 58](https://user-images.githubusercontent.com/82064173/132739358-140ab152-9dbe-4280-8727-88fcfe07a486.jpg)

   The 4 toggles in the image above are the default and are defined by:
   ```
   "Fast Monsters" "-fast"
   "No Monsters" "-nomonsters"
   "Respawn Monsters" "-respawn"
   "Solo Net" "-solo-net"
   ```
   
   "Text that appears in the launcher" "Parameter"
   
## 4. Change the Bottom Row Type
   
   1 = The bottom row can either be the default "Fullscreen + Resolution" boxes
   
   or
                          
   2 = You can customise the contents of 2 different boxes
   
   Change the number that appears to 2 if you want to customise it. Leave it as 1 to stay with the "Fullscreen + Resolution"
   
## 5. Customise the Bottom Row (Only if you chose 2)

   ```
+"Time"
"-time_use"
"-time_keys"
"-time_secrets"
"-time_all"

+"Stats"
"-levelstat"
"-analysis"
"both"
   ```
   
   ___
   
   +"Text on top of the boxes"
   
   "Parameter"
   
   "Another Parameters"
   
   "etc"
   
   ___
   
   If the last option is "both" or "all", then it will use every parameter in that drop down menu			
   
   ex: -levelstat -analysis	
   
   
# Messed up?

 If you messed up and can't get it to work, note that deleting the file will make the launcher reset it to default when restarting the launcher
