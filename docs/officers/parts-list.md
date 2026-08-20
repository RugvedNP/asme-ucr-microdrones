# Parts list and budget

Planning doc for officers. Doubles as the source for sponsorship asks — the
2026–2027 packet lists the project's needs as *"Microdrones, controllers,
batteries, tiny motors, travel,"* and this page is where those become real
line items.

> **TODO before submitting any sponsorship ask:** fill in the price columns
> and the member count. Prices are deliberately blank — put in real quotes,
> not estimates, since these numbers go in front of sponsors.

## Sizing

| | |
|---|---|
| Members expected | **TODO** |
| Members per drone | 2 (per the packet) |
| Drones needed | **TODO** — members ÷ 2, round up |
| Spare drones (breakage) | recommend +2 |

## Per drone — Fall build (flix, brushed)

| Part | Qty | Unit | Total | Notes |
|---|---|---|---|---|
| ESP32 Mini board | 1 | TODO | TODO | Order as "WEMOS D1 MINI ESP32" |
| GY-91 IMU board (MPU-9250) | 1 | TODO | TODO | |
| 8520 brushed motor, 3.7V | 4 | TODO | TODO | 2× CW, 2× CCW |
| UMW 100N03A MOSFET | 4 | TODO | TODO | One per motor |
| 10kΩ resistor | 6 | TODO | TODO | 4 pull-down + 2 voltage divider |
| 1S LiPo, 850mAh, ≥25C | 2 | TODO | TODO | 2 per drone so a pair isn't idle while charging |
| Propellers (A and B) | 4 + spares | TODO | TODO | **Order generously — these break constantly** |
| 3D-printed frame | 1 | filament | TODO | Printed in-house |
| Hookup wire, connectors, switch | — | TODO | TODO | |
| SBUS RC receiver *(optional)* | 1 | TODO | TODO | Only if not flying via USB gamepad |
| | | **Per-drone subtotal** | **TODO** | |

## Per drone — Winter build (ESP-FC, brushless)

Meaningfully more expensive than the Fall build. Budget for it early.

| Part | Qty | Unit | Total | Notes |
|---|---|---|---|---|
| ESP32 or ESP32-S3 board | 1 | TODO | TODO | |
| SPI gyro (ICM20602 / BMI160 / MPU6050) | 1 | TODO | TODO | |
| Brushless motor, 1103–1204 | 4 | TODO | TODO | |
| 4-in-1 ESC, DShot-capable | 1 | TODO | TODO | BLHeli_S or better |
| ELRS/CRSF receiver | 1 | TODO | TODO | |
| 1S LiPo (higher C rating) | 3 | TODO | TODO | Brushless draws harder |
| 2.5–3.5" frame + props | 1 set | TODO | TODO | |
| | | **Per-drone subtotal** | **TODO** | |

## Shared club equipment

Bought once, used by everyone. This is often the easier sponsorship ask —
it's durable equipment, not consumables.

| Item | Qty | Cost | Priority |
|---|---|---|---|
| Soldering station | TODO | TODO | **Critical** |
| Solder, flux, wick, tips | — | TODO | **Critical** |
| 1S LiPo charger (multi-port) | TODO | TODO | **Critical** |
| LiPo-safe charging bags | TODO | TODO | **Critical — safety** |
| Safety glasses | 1/member | TODO | **Critical — safety** |
| Multimeter | TODO | TODO | High |
| Helping-hands / PCB holder | TODO | TODO | High |
| USB gamepad controller | TODO | TODO | High |
| RC transmitter (shared) | TODO | TODO | Medium |
| 3D printer filament | TODO | TODO | High |
| Spare-parts bin stock | — | TODO | High |
| FPV goggles | TODO | TODO | Later — Spring |
| Obstacle course materials (gates, nets) | — | TODO | Later — Spring |

## Travel

The packet names travel as a funding need, for competing against other
schools (UC Davis, UCLA are named as targets).

| Line | Cost | Notes |
|---|---|---|
| Transport to competitions | TODO | Depends on host and distance |
| Registration/entry fees | TODO | **TODO: confirm whether target events charge** |
| Lodging (if overnight) | TODO | |

## Mapping to sponsorship tiers

For reference when writing asks — tiers from the 2026–2027 packet:

| Tier | Amount | Could fund |
|---|---|---|
| Bronze | ≥ $500 | Consumables for a quarter: props, batteries, solder |
| Silver | ≥ $1,000 | A set of complete Fall microdrone kits |
| Gold | ≥ $2,500 | Winter brushless builds, or the shared equipment list |
| Platinum | ≥ $5,000 | Full-year program including travel to inter-school competition |

Donations are tax-deductible **only** through the UC Riverside Donation
Portal or made payable to "UCR Foundation" (501(c)(3)). Parts and discounts
count toward tier level as well as cash.

## Ordering notes

- **Over-order props and batteries.** They are the two things that run out
  mid-quarter and stall every pair at once.
- Lead times matter — order Winter brushless parts during Fall, not in week 1
  of Winter.
- Keep a running "broken/needs reorder" list; the Parts & Inventory role in
  [roles.md](roles.md) owns it.
