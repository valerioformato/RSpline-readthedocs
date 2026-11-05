"""NAIA-style Sphinx/MyST manual; building it requires no ROOT installation."""

project = "RSpline"
author = "Valerio Formato"
copyright = "Valerio Formato"
release = "1.0.0"
version = "1.0"

extensions = [
    "myst_parser",
    "sphinx.ext.duration",
    "sphinx.ext.mathjax",
]
source_suffix = {".md": "markdown", ".rst": "restructuredtext"}
master_doc = "index"
exclude_patterns = []
nitpicky = True
myst_enable_extensions = ["dollarmath", "colon_fence"]
html_theme = "furo"
html_title = "RSpline manual"
html_show_sourcelink = True
