Contributing to the Majora's Mask Decompilation Project
=======================================================

Thanks for helping us reverse engineer *The Legend of Zelda: Majora's Mask* for the N64! 
All contributions are welcome. This is a group effort, and even small contributions can make a difference. Some tasks also don't require much knowledge to get started.

This document is meant to be a set of tips and guidelines for contributing to the project.
For general information about the project, see [our readme](https://github.com/zeldaret/mm/blob/master/README.md).

Most discussions happen on our [Discord Server](https://discord.zelda64.dev), where you are welcome to ask if you need help getting started, or if you have any questions regarding this project and other decompilation projects.


Useful Links
------------

- [Discord](https://discord.zelda64.dev/) - Primary discussion platform.
- [Trello board](https://trello.com/b/ruxw9n6m/majoras-mask-decompilation) - We use this to track decompilation progress, not GitHub Issues.

- [Installation guide](https://github.com/zeldaret/mm/blob/master/README.md#installation) - Instructions for getting this repository set up and built on your machine.
- [Zelda 64 Reverse Engineering Website](https://zelda64.dev/) - Our homepage, with links to other resources.
- [Introduction to OOT decomp](https://github.com/zeldaret/oot/blob/master/docs/tutorial/contents.md) - A very detailed tutorial on how to get started with decomp. For OOT, but largely applicable to MM as well.
- The `#resources` channel on the Discord contains many more links

Getting Started
---------------

### What should I know to take part?

Basic knowledge of C, particularly arrays and pointers, is extremely useful. Knowledge of MIPS is not required initially, you can pick it up as you work through some decompilation.

You should be familiar with using git and GitHub. There are a number of tutorials available online, [such as this one](https://github.com/firstcontributions/first-contributions), which can help you get started.

The most useful knowledge to have is a general understanding of how the game works. An afternoon of constructive mucking about in the [OOT Practice Rom](http://practicerom.com/) (aka GZ) or the [MM Practice Rom](https://kz.zeldacodes.org/) (aka KZ) will be very beneficial if you have not looked at either of the N64 Zelda's internals before.
The [OOT Decompilation Project](https://github.com/zeldaret/oot) is farther along than this project, so it can also be a great resource.

This project only uses *publicly available code*.
Anyone who wishes to contribute to the OOT or MM projects **must not have accessed leaked source code at any point in time** for Nintendo 64 SDK, iQue player SDK, libultra, Ocarina of Time, Majora's Mask, Animal Crossing/Animal Forest, or any other game that shares the same game engine or significant portions of code to a Zelda 64 game or any other console similar to the Nintendo 64.

### Environment Setup

Get started by following the [installation guide in the readme](https://github.com/zeldaret/mm/blob/master/README.md#installation).
When successful, you should be able to build a matching ROM before you start making any changes.

### First Contribution

Usually, the best place to get started is to decompile an actor overlay. 
An *actor* is any thing in the game that moves or performs actions or interactions: Link is an actor, enemies are actors, NPCs are actors, etc.

You should [join the Discord](https://discord.zelda64.dev/) to say hello and get suggestions on where to start on the `#mm-decomp` channel.

We track who is working on what on the [Trello board](https://trello.com/b/ruxw9n6m/majoras-mask-decompilation).
After joining the Discord, ask to be added to the Trello board so you can claim your actor and avoid duplicate work.

Style Guide & Conventions
-------------------------

Most of the C formatting style is enforced by the `format.sh` script, which is based on `clang-format`.
Running `./format.sh` will apply our standard style to all `.c` files in the repository.

There are some conventions that cannot be automatically enforced.

### Naming Scheme

The following overlays are good examples of our naming conventions:

- [`ovl_Dm_Ravine`](src/overlays/actors/ovl_Dm_Ravine/z_dm_ravine.c)
- [`ovl_En_Jc_Mato`](src/overlays/actors/ovl_En_Jc_Mato/z_en_jc_mato.c)

These files demonstrate the following:

- Word order in names are from least-to-most specific (`DM_RAVINE_STATE_ACTIVE`, not `DM_RAVINE_ACTIVE_STATE`)
- Functions, structs, unions, enums, and typedefs are `TitleCase` (`DmRavine`)
    - "Methods" for objects separate the object from the verb with an underscore (`DmRavine_Init`)
- Variable names are `camelCase` (`actionFunc`)
    - Global variables start with `g` (`gSaveContext`)
    - Static global variables start with `s` (`sSphereInit`)
- Macros and enum constants are `SCREAMING_SNAKE_CASE` (`DM_RAVINE_STATE_ACTIVE`)
- Auxiliary structs, enums, and constants are defined in the header file
- Trailing commas in array and struct definitions (see `EnJcMatoDamageTable`)
- Constants converted to whichever looks best in context: hexadecimal, decimal, float, or boolean
    - Rotation angles should always be in hexadecimal
- Define macros for bitwise access to `actor->params`

### `NON_MATCHING`

If you make significant progress on decompiling a function, but can't get it to match perfectly, you can use a `NON_MATCHING` block to commit your code but have it excluded from the build, like so:

```c
#ifdef NON_MATCHING
void CollisionCheck_SpawnWaterDroplets(GlobalContext* ctxt, Vec3f* v) {
    // ... 
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_collision_check/CollisionCheck_SpawnWaterDroplets.asm")
#endif
```

Before using `NON_MATCHING`, first try to use the [decomp-permuter](tools/decomp-permuter) tool to find a closer match.

### Matching vs. Documenting

Usually, the first step of decompiling a section of code is to get it *matching*: to produce a C version of the code that can be compiled into an identical ROM.

However, the goal of this project is to produce a codebase that can be understood and modified.
So, beyond producing matching C code, the next steps are *documenting* the code.

Documenting is more than just adding comments, and entails:

- Renaming functions, variables, and struct members
- Using (or adding) constants, enums, and macros when possible
- Explaining sections of code that are not straightforward

Overlays are not required to be documented at this time, but `code/` and `boot/` are.
When an overlay documentation has been started, it will be required to be completed.

For right now, object segment symbols should not be documented/renamed.
These will be given names when object reconstruction is ready.
However, it can be useful to add comments with name suggestions.


Pull Requests (PRs)
-------------------

### Checklist

Before opening a PR, walk through the following steps to ensure that your code conforms to the style guide & conventions.

- `./format.sh` was run to apply standard formatting.
- `make` successfully builds a matching ROM.
- No new compiler warnings were introduced during the build process
- New variables & functions should follow standard naming conventions.
- Comments and variables have correct spelling.

### Pull Request Process

After opening a PR, the Jenkins server will verify your changes.
If there is an error, double-check that you can successfully `make clean && make` locally and that all added/modified files were `git add`-ed to your commit.

Each PR needs a review from one reviewer, plus the project lead.

The PR author marks the comments as resolved: the commenter may not have permissions to do so.
Once all comments are addressed, it is courteous to ping the reviewer on either Discord or GitHub via re-requesting a review.

After all the comments are addressed and at least one contributor has approved the review, the project lead can then merge the code.
The project lead is also responsible for ensuring that all of these procedures are followed.

Throughout the PR process, you (the author) should update the card on [Trello board](https://trello.com/b/ruxw9n6m/majoras-mask-decompilation) with the appropriate column and labels.
