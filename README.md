# Tutorial-STM32
This repo contains tutorial code for the NUCLEO-G474RE STM32 devkit

## Note
- All commits should be in the following format: `<TaskId>:<description>`
  - TaskId: The task id as given in the Finch Systems Activity Tracker
 (ex: FIRM1-1)
  - Description: brief explanation of what occured in this commit
- This README file is written in Markdown syntax

## Github Command Line Commands
Download the repository with the following command:
```
git clone https://github.com/spacesys-finch/Tutorial-STM32.git
```

In order to push code changes from your local computer onto the remote server (github), perform the following commands:

Tell git which files are to be pushed onto the server:
```
git add <fileName>
```

Save your added files using (replace the words within <>):
```
git commit -m "<TaskId>:<description>"
```

Put your saved changes onto the server:
```
git push
```
Your files should now be on the server. Note that you can check the state of your files at any time using: 
```
git status
```