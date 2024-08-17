# Super Flamingo Quest

### Build

```sh
cmake -B build
cmake --build build
mv build/super_flamingo_quest ./super_flamingo_quest
```

### Play

```sh
./super_flamingo_quest
```

---

You're Flamingo, you're searching Happiness. Good Luck!

Links uteis:
Sound Effect - https://sfbgames.itch.io/chiptone
Music - https://www.beepbox.co


The keys are NOT a Leaf's Odyssey Reference


Health
Hope -> Recovers 1 Heart at the start of each level
Resilience -> Recovers with time
Power -> Recovers eating
Courage -> Recovers manually with: Healing spell, Health altar, Health potion
Wisdom -> Recovers at the end of a level, time left in clock is converted to health

Magic
Wind -> Recovers with time
Party -> Recovers with potions and altars
Fun -> 
Harder -> Recovers when you take damage
Eloise ->

All Magic sources recover when you eat a fruit of their color (very slow)


Spells

Tier 1 spells
(wind) Wind hop -> Boosts you into a horizontal direction.
(party)
(fun) speed dial -> Gives you triple speed when activated, drains slowly.
(hard) Spear of Courage -> Shoots a spear that kills the first enemy it hits.
(eloise) Transmutation -> Turns a Heart Shard or a Pearl Shard into their next version in the cycle (Yellow-Green-Blue-Red-Orange-Yellow).

Tier 2 spells
(wind) Seer -> Reveals all secrets on screen
(party) Shield -> Makes you invulnerable to enemies while activated, drains slowly.
(fun) Healing burst -> Heals Courage.
(hard)
(eloise) Transfiguration -> Turns a Heart Shard into a Pearl Shard and vice-versa. (wind = hope)

Tier S spells

(voice) Stops time
(all) Fills one voice


Secret bars! (as if 5 health and 5 mana bars weren't enough)

--- Soul bar
If you have 0 health in all 5 bars, your soul becomes vulnerable.
All damage will be dealt directly to your soul unless you have any of the other 5 quests to protect it.
If you reach 0 soul, game over.

Maybe if any bar is at 0, you'll also slowly take soul damage!
To encourage players not to drop an "inconvinient" bar to 0

--- Voice bar
Used to cast powerful spells
Shards of voice are REALLY rare to find (only 9 shards in the entire game?)
Recovers voice by consuming all 5 health bars and all 5 mana bars.
Maybe use it as extra health? or do it separetely...

--- World bar
Used to cast spells
Recovers by killing enemies
does it have shards??? what to do? (undecided)





Levels will be measured by complexity points.
Each collectable costs a complexity point
Each enemy costs a complexity point
each puzzle structure (keys and gates, levers, platforming, travel distances) costs complexity points

If a level has 70 complexity points, it can only have 70 points worth of collectables and 70 points worth of challenge.
