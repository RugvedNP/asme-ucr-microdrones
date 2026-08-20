# Simulator setup

Use this if you don't have hardware yet — waiting on parts, joined
mid-quarter, or your drone is out of action. The flix repo ships a Gazebo
simulator you can fly with a gamepad.

Officers: offer this proactively. A member with nothing to do for two weeks
usually stops coming.

---

```
Help me set up the flix Gazebo simulator on my machine. I'm running [YOUR OS: Ubuntu 22.04 / Ubuntu 24.04 / macOS with Homebrew / WSL2 on Windows].

Walk me through:
1. Installing Gazebo (which version does flix need?)
2. Building the simulation plugin from the flix repo
3. Launching the simulator
4. Connecting a USB gamepad or keyboard for control
5. What the expected behavior should look like when it's working correctly

Reference: https://github.com/okalachev/flix/blob/master/gazebo/README.md

If there are any known issues with my OS version, flag them and provide workarounds.
```

## Note for Windows users

Most of the club is on Windows. The simulator path is smoothest under WSL2 —
say so in the prompt, and expect some extra setup around graphics passthrough.

The flix repo is already checked out in this project at
[`../../build1-flix/flix/`](../../build1-flix/flix), including its
[`gazebo/`](../../build1-flix/flix/gazebo) directory, so you don't need to
clone it again.
