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
CI follows NAIA: `build:docker` uses `sphinxdoc/sphinx`, installs requirements
in a fresh virtual environment and runs `make html`. This avoids conflicts when
upgrading packages preinstalled in the image, including `roman-numerals-py`.
Read the Docs uses the configured Python 3.12 toolchain.
Missing local references and Sphinx warnings fail the build.

## Read the Docs setup

Import this repository as a Sphinx project and keep `.readthedocs.yaml` at its
root. The configuration selects Ubuntu 24.04, Python 3.12, the requirements file,
and `docs/source/conf.py`, with warnings treated as errors. Enable the default
branch and any desired release versions in the hosting project.

The project dashboard and build history are available at
[RSpline on Read the Docs](https://app.readthedocs.org/projects/rspline/).

The configuration follows the official
[Read the Docs v2 reference](https://docs.readthedocs.com/platform/stable/config-file/v2.html).

## Webhook deployment

GitLab CI builds the HTML artifact. Read the Docs builds and publishes its own
copy when notified by the repository webhook; no deployment job is needed in CI.
The webhook is configured in the services, not in `.gitlab-ci.yml`.

After creating/importing the Read the Docs project:

1. In Read the Docs, open **Admin > Integrations** and add a **GitLab**
   integration if one does not already exist. Use its generated webhook URL
   and secret token, rather than another project's integration.
2. In [RSpline-docs > Settings > Webhooks](https://gitlab.cern.ch/ams-italy/docs/RSpline-docs/-/hooks),
   add that URL and secret token. Enable **Push events**, **Tag push events**
   and **Merge request events**, and keep SSL verification enabled.
3. Test a push delivery in GitLab, then confirm that Read the Docs receives
   the event and completes a build. Enable `latest` for `master` and any desired
   release versions in Read the Docs.

The Read the Docs project must exist before its integration can be configured.
Keep the integration secret in the service settings. The procedure follows the
[official GitLab integration guide](https://docs.readthedocs.com/platform/stable/guides/setup/git-repo-manual.html).

## Maintaining the manual

The target API is RSpline 1.0.0 with the linked TF1 and validation changes through
`9d9640a`. The source remains authoritative. When changing numerical/API behavior,
update the matching Doxygen contracts in RSpline and these tutorial pages.

The two programs in `docs/examples` mirror RSpline's installed-package examples.
They are included literally in the tutorials and were compiled and run against
the matching installed library. Keep these snapshots synchronized with the
C++ repository's `examples/interpolation.cpp` and `examples/fitting.cpp`.
