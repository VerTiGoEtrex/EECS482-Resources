ca.py will print all repos to stdout that are in the EECS 482 org.

Update the token in the script to authenticate.

To clone using this script, I'd recommend something like this
python ca.py | grep -e '\.4' | xargs -I{} git clone git@github.com:{}.git
