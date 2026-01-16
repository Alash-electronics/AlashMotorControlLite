#!/bin/bash

# Script to create remaining language-specific examples
# Remaining: DirectionChange, ESP32_Mecanum_4WD_Demo, ESP32_Mecanum_Serial,
#           GettersDemo, MultiMotorSync, SmoothSpeed, SpeedLimits

cd /Users/beksultanajten/AlashMotorControlLite/examples

# Array of remaining examples
examples=(
  "DirectionChange"
  "ESP32_Mecanum_4WD_Demo"
  "ESP32_Mecanum_Serial"
  "GettersDemo"
  "MultiMotorSync"
  "SmoothSpeed"
  "SpeedLimits"
)

for example in "${examples[@]}"; do
  echo "Processing $example..."

  # Create RU version (copy original with language header)
  if [ -f "$example/$example.ino" ]; then
    echo "// Language: Русский | English: ../EN/$example/ | Қазақ: ../KZ/$example/" > "RU/$example/$example.ino"
    cat "$example/$example.ino" >> "RU/$example/$example.ino"
    echo "  ✓ RU/$example created"

    # Create KZ version (copy from RU for now)
    echo "// Language: Қазақ | English: ../EN/$example/ | Русский: ../RU/$example/" > "KZ/$example/$example.ino"
    echo "// TODO: Translate comments and strings to Kazakh" >> "KZ/$example/$example.ino"
    cat "$example/$example.ino" >> "KZ/$example/$example.ino"
    echo "  ✓ KZ/$example created (needs translation)"

    echo "  ⏳ EN/$example needs manual English translation"
  else
    echo "  ✗ Original file not found: $example/$example.ino"
  fi

  echo ""
done

echo "=========================================="
echo "Summary:"
echo "- RU versions: Created with language headers"
echo "- KZ versions: Created (need Kazakh translation)"
echo "- EN versions: Need manual English translation"
echo ""
echo "Next step: Translate Russian to English for EN/ versions"
echo "=========================================="
