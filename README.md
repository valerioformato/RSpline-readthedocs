# RSpline manual

The separate user manual for [RSpline](https://gitlab.cern.ch/ams-italy/rspline),
following NAIA's manual structure: Sphinx, MyST Markdown and the Furo theme.
The C++ repository owns the Doxygen API reference; this project owns tutorials
and narrative guidance. Building the manual does not clone/build RSpline and
requires no ROOT or analysis datasets.

## Build locally

Use Python 3.12 or newer:

```sh
python3 -m venv .venv
. .venv/bin/activate
python -m pip install -r docs/requirements.txt
python -m sphinx -n -W --keep-going -b html docs/source docs/build/html
```

Open `docs/build/html/index.html`. `make -C docs html` runs the same strict
HTML build. Requirements are pinned, including transitive dependencies, and
CI uses the same Python 3.12 toolchain as Read the Docs. Missing local references
and Sphinx warnings fail the build.

## Read the Docs setup

Import this repository as a Sphinx project and keep `.readthedocs.yaml` at its
root. The configuration selects Ubuntu 24.04, Python 3.12, the requirements file,
and `docs/source/conf.py`, with warnings treated as errors. Enable the default
branch and any desired release versions in the hosting project. Repository
creation/import and an actual hosted URL are separate from generating this site;
no public hosting address is assumed in the manual.

The configuration follows the official
[Read the Docs v2 reference](https://docs.readthedocs.com/platform/stable/config-file/v2.html).

## Maintaining the manual

The target API is RSpline 1.0.0 with the linked TF1 and validation changes through
`9d9640a`. The source remains authoritative. When changing numerical/API behavior,
update the matching Doxygen contracts in RSpline and these tutorial pages.

The two programs in `docs/examples` mirror RSpline's installed-package examples.
They are included literally in the tutorials and were compiled and run against
the matching installed library. Keep these snapshots synchronized with the
C++ repository's `examples/interpolation.cpp` and `examples/fitting.cpp`.
