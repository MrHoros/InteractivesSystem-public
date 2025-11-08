# InteractivesSystem-public

This is an interactive system from my newest action-adventure game project.

You can check the game here:

Itch.io
https://brruhba.itch.io/luntrus-project

Video:
https://drive.google.com/drive/u/1/folders/11HIc2cwJlTuMV8cEMRwkN__Wu1C5apqX


**InteractiveComponent**
<br>- Add this to an actor to add the interactive system to an actor and choose what type of interactive you want.
Default: Checks for objects that have implemented Interact() from InteractiveInterface
Document: creates UDocument. You can set the title and text directly in BP
Hint: creates UHint

**ProximityPromptComponent**
 <br>- Create "Interact" input key and add this component to an actor to add the 'interaction by key' feature. Inherit from it and override functions in BP to create popups or desired functionality when a player observes the object or enters its activation range.

