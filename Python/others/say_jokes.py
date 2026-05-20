import pyttsx3
import pyjokes

engine = pyttsx3.init()

for i in range(1, 11):
    joke = pyjokes.get_joke()
    print(f"{i}. {joke}")
    engine.say("Joke number " + str(i))
    engine.runAndWait()
    engine.say(joke)
    engine.runAndWait()
