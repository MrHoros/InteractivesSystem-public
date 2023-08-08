# InteractivesSystem-public

This is an interactive system from my newest action-adventure game project.

InteractiveComponent
Add this to an actor to add the interactive system to an actor and choose what type of interactive you want.
Default: Checks for objects that have implemented Interact() from InteractiveInterface
Document: creates UDocument. You can set the title and text directly in BP
Hint: creates UHint

ProximityPromptComponent
Create "Interact" input key and add this component to an actor to add the 'interaction by key' feature. Inherit from it and override functions in BP to create popups or desired functionality when a player observes the object or enters its activation range.

