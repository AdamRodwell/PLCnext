#!/usr/bin/env bash
# update_build_targets.sh
# Reads the Docker image tag from .devcontainer/devcontainer.json and updates <Target> in all .proj files.
#
# Image tag format:  axcf2152-linux_sdk-2024.0.9_LTS-24.0.9.199
# Target format:     AXCF2152,2024.0.9 LTS (24.0.9.199)

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DEVCONTAINER_FILE="${REPO_ROOT}/.devcontainer/devcontainer.json"

# Extract the image tag (everything after the last colon on the "image": line)
IMAGE_TAG=$(grep '"image":' "$DEVCONTAINER_FILE" | head -1 | sed 's|.*:||' | tr -d '[:space:]",')

if [[ -z "$IMAGE_TAG" ]]; then
    echo "ERROR: Could not read image tag from ${DEVCONTAINER_FILE}"
    exit 1
fi

echo "Image tag: ${IMAGE_TAG}"

# Parse tag: axcf2152-linux_sdk-2024.0.9_LTS-24.0.9.199
# Split on '-' — fields: [controller, linux_sdk, version_LTS, build]
IFS='-' read -ra PARTS <<< "$IMAGE_TAG"

if [[ ${#PARTS[@]} -lt 4 ]]; then
    echo "ERROR: Unexpected image tag format '${IMAGE_TAG}'"
    echo "Expected: <controller>-linux_sdk-<version>_LTS-<build>"
    exit 1
fi

CONTROLLER="${PARTS[0]^^}"                         # axcf2152 -> AXCF2152
VERSION_RAW="${PARTS[2]}"                          # 2024.0.9_LTS
BUILD="${PARTS[3]}"                                # 24.0.9.199
VERSION="${VERSION_RAW//_/ }"                      # 2024.0.9_LTS -> 2024.0.9 LTS
VERSION="${VERSION^^}"                             # ensure uppercase (e.g. lts -> LTS)

TARGET="${CONTROLLER},${VERSION} (${BUILD})"

echo "Target:    ${TARGET}"
echo ""

# Update all .proj files
mapfile -t PROJ_FILES < <(find "$REPO_ROOT/src" -name "*.proj" 2>/dev/null)

if [[ ${#PROJ_FILES[@]} -eq 0 ]]; then
    echo "No .proj files found under src/"
    exit 0
fi

for PROJ in "${PROJ_FILES[@]}"; do
    RELATIVE="${PROJ#${REPO_ROOT}/}"
    if grep -q "<Target>" "$PROJ"; then
        sed -i "s|<Target>.*</Target>|<Target>${TARGET}</Target>|" "$PROJ"
        echo "  Updated: ${RELATIVE}"
    else
        echo "  Skipped (no <Target>): ${RELATIVE}"
    fi
done

echo ""
echo "Done. Set target to: ${TARGET}"
