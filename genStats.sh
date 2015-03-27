#!/bin/bash

blue=$(tput setaf 4)
normal=$(tput sgr0)

nrOfTeams=$(gfind -mindepth 1 -maxdepth 1 -type d | wc -l)
nrOfTeamsWSubmit=$(gfind -mindepth 1 -maxdepth 1 -type d | xargs -I{} sh -c "echo '{}'; git --git-dir={}/.git --work-tree=/Users/ncrocker/IA/repos/{} describe 2>&1" | grep -B 1 submission | grep -e "\./.*" | wc -l)
#Get number of people who have not committed at all
nrOfTeamsWNoCommits=$(gfind -mindepth 1 -maxdepth 1 -type d | xargs -I{} git --git-dir={}/.git --work-tree=/Users/ncrocker/IA/repos/{} rev-parse HEAD 2>&1 | grep fatal | wc -l)
nrOfSubmissions=$(gfind -mindepth 1 -maxdepth 1 -type d | xargs -I{} git --git-dir={}/.git --work-tree=/Users/ncrocker/IA/repos/{} tag -l | wc -l)
submissionAggregates=$(gfind -mindepth 1 -maxdepth 1 -type d | xargs -I{} git --git-dir={}/.git --work-tree=/Users/ncrocker/IA/repos/{} tag -l | sort | grep -o "2015.[0-9]\+.[0-9]\+" | uniq -c)
avgLinesInFile=$(gfind -type f -name pager.c* -exec wc -l {} \; | cut -d ' ' -f1 | awk '{sum+=$1}END{printf "Sum=%d\nCount=%d\nAve=%.2f\n",sum,NR,sum/NR}')
lastSubmitDates=$(gfind -mindepth 1 -maxdepth 1 -type d | xargs -I{} sh -c "echo '{}'; git --git-dir={}/.git --work-tree=/Users/ncrocker/IA/repos/{} describe 2>&1" | grep -o "2015.[0-9]\+.[0-9]\+" | sort | uniq -c)

printf "Out of ${blue}%s${normal} teams, ${blue}%s${normal} have made at least one submit\n" "$nrOfTeams" "$nrOfTeamsWSubmit"
avgSubmissions=$(bc -l <<< "$nrOfSubmissions/$nrOfTeamsWSubmit")
printf "There have been ${blue}%s${normal} submissions to date, making the average ${blue}%.4s${normal} submits per team (who have submitted)\n" "$nrOfSubmissions" "$avgSubmissions"
printf "${blue}%s${normal} have yet to commit anything... Better get started...\n" "$nrOfTeamsWNoCommits"
printf "The file pager.c* has the following stats: %s\n" $avgLinesInFile
printf "The submission histogram is as follows\n"
echo "$submissionAggregates"
printf "The last submission dates for all teams is as follows\n"
echo "$lastSubmitDates"
