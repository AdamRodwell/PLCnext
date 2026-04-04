#!/usr/bin/env bash
# update_project_list.sh
# Scans src/projects/ for directories containing a plcnext.proj file and updates
# the "project_name" pickString options in .vscode/tasks.json.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TASKS_FILE="${REPO_ROOT}/.vscode/tasks.json"

if [[ ! -f "$TASKS_FILE" ]]; then
    echo "ERROR: tasks.json not found at ${TASKS_FILE}"
    exit 1
fi

# Find all project names (directories under src/projects/ that contain a plcnext.proj)
mapfile -t PROJECTS < <(
    find "${REPO_ROOT}/src/projects" -maxdepth 2 -name "plcnext.proj" \
    | sed "s|${REPO_ROOT}/src/projects/||" \
    | sed 's|/plcnext.proj||' \
    | sort
)

if [[ ${#PROJECTS[@]} -eq 0 ]]; then
    echo "No PLCnext projects found under src/projects/"
    exit 0
fi

echo "Found projects:"
for P in "${PROJECTS[@]}"; do
    echo "  - ${P}"
done

# Build the JSON array of option objects for a pickString input
# Format: [{"label":"A","value":"A"},{"label":"B","value":"B"},...]
OPTIONS_JSON="["
for i in "${!PROJECTS[@]}"; do
    P="${PROJECTS[$i]}"
    OPTIONS_JSON+="{\"label\":\"${P}\",\"value\":\"${P}\"}"
    if [[ $i -lt $(( ${#PROJECTS[@]} - 1 )) ]]; then
        OPTIONS_JSON+=","
    fi
done
OPTIONS_JSON+="]"

# Use python3 to do a safe in-place JSON edit
python3 - "$TASKS_FILE" "$OPTIONS_JSON" <<'EOF'
import json, sys

tasks_path = sys.argv[1]
options = json.loads(sys.argv[2])

with open(tasks_path, "r") as f:
    data = json.load(f)

updated = False
for inp in data.get("inputs", []):
    if inp.get("id") == "project_name":
        inp["type"] = "pickString"
        inp["options"] = options
        # Set default to first project
        if options:
            inp["default"] = options[0]["value"]
        updated = True
        break

if not updated:
    print("WARNING: 'project_name' input not found in tasks.json — no changes made.")
    sys.exit(0)

with open(tasks_path, "w") as f:
    json.dump(data, f, indent=4)
    f.write("\n")

print("tasks.json updated successfully.")
EOF

echo ""
echo "Done. project_name options set to: $(IFS=', '; echo "${PROJECTS[*]}")"
