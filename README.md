# philosophers

A Codam project about thread synchronisation and survival of the fattest.

## philo who?
This is a variation of the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) concerning access to a shared resource.

- Between 1 and 200 philosophers sit around a table
- There are as many forks as there are philosophers
- Each fork is placed between two philosophers sitting next to each other
- Each philosopher must eat, sleep and think (in that order)
- A philosopher can only eat if they hold two forks
- Once a philosopher has eaten a meal, they put both forks down and start sleeping
- The philosophers do not communicate with each other

The input contains indication of the time necessary to eat a meal (time to eat), the lenght of the sleep (time to sleep) and the maximum time that may pass 
between the start of two consecutive meals for the philosopher to survive (time to die).

## concepts I got to practice:
- threads and mutexes
- synchronisation
- letting go (because there is only so much you can control)

## wanna see?
The executable is called `philo` and should be accompanied by the following arguments: `number of philosophers` `time to die` `time to eat` `time to sleep`. 

Optionally, a fifth argument may be added: `number of meals` -> this will make the simulation stop once all philosophers have eaten that many meals.

For example: `./philo 200 410 200 200` will keep running without anyone dying.
