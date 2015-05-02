#!/usr/bin/env python
# encoding: utf-8

from github import Github
import re

# CONFIG
TOKEN = 'UPDATEME'
BLACKLIST = ["necrocke",
        "jflinn",
        "schmatz",
        "tjfryan",
        "tjryan",
        "coo",
        "ncnuech",
        "mcluaghn",
        "amodell",
        "ausmal",
        "bhekman",
        "honey",
        "mclaughn"]
# /CONFIG

b = Github(TOKEN)

org = b.get_organization("eecs482")
repositories = org.get_repos()
for repo in repositories:
    if re.match(r'^eecs482/(' + '|'.join(BLACKLIST) + r')\.[0-4]', repo.full_name) is None:
        print repo.full_name

