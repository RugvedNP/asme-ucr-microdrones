# Frame modification

Use when adapting the 3D-printed flix frame — different IMU board, different
motors, or a mounting change.

Measure your board before you start. Guessed dimensions produce a frame that
doesn't fit and a wasted print.

---

```
I'm modifying the flix 3D-printed frame to accommodate a different IMU board. The original frame is designed for the GY-91 board with M3 mounting holes spaced [MEASURE AND INSERT: e.g. 17mm x 17mm].

My new IMU board is: [YOUR BOARD, e.g. GY-521 (MPU-6050)]
Its mounting hole spacing is: [MEASURE AND INSERT: e.g. 15.2mm x 15.2mm]
Its board dimensions are: [MEASURE AND INSERT: e.g. 20mm x 16mm]

The original flix frame STEP file is at: build1-flix/flix/docs/assets/flix-frame-1.1.step

Help me:
1. Identify which features in the STEP file define the IMU mounting holes
2. Calculate the coordinate changes needed to move the mounting posts
3. If I'm editing in [YOUR CAD: FreeCAD / Fusion 360 / OnShape], give me step-by-step instructions to modify the hole positions
4. Flag any structural concerns (will moving the holes weaken the arm roots? change the center of gravity?)
5. Suggest print settings if the modified area is thinner than the original
```

## Before you print

- **Save modified frames back to this repo** so the next person can print
  yours instead of redoing the work.
- Note *why* you changed it in the commit message — "GY-521 instead of GY-91"
  tells the next member whether your version applies to them.
- Print one, check fit, *then* print four.

ASME runs SOLIDWORKS workshops — if you're new to CAD, that's a faster start
than learning from a prompt.
