#!/bin/bash

action=$1
env=$2

pull() {
    UNCOMMITTED_CHANGES=$(git status --porcelain=v1 2>/dev/null | wc -l)

    if [[ $UNCOMMITTED_CHANGES -eq 0 ]]
    then 
      theme download --env=$env
      
      UNCOMMITTED_CHANGES_2=$(git status --porcelain=v1 2>/dev/null | wc -l)
      if [[ $UNCOMMITTED_CHANGES_2 -eq 0 ]]
      then
        echo -e "\nCommitting changes from shopify...\n"
        git add -A
        git commit -m 'changes from shopify'
        git push
      fi
    else 
      echo -e "\nCommit your current changes before pulling from shopify!!!\n"
      exit 0
    fi
}

cd theme

case $action in
  pull)
    pull
    ;;

  deploy)
    UNCOMMITTED_CHANGES=$(git status --porcelain=v1 2>/dev/null | wc -l)

    if [[ $UNCOMMITTED_CHANGES -eq 0 ]]
    then 
      case $env in
        development | staging)
          theme deploy --env=$env
          ;;

        production)
          theme deploy --env=$env --allow-live
          ;;
      esac
    else 
      echo -e "\nCommit your current changes before deploying to shopify!!!\n"
      exit 0
    fi

    ;;

  watch)
    echo -e "\nWatching theme files...\n"
    
    case $env in
      development | staging)
        (trap 'kill 0' SIGINT; theme watch --env=$env & yarn dev:res)
        ;;

      production)
        (trap 'kill 0' SIGINT; theme watch --env=$env --allow-live & yarn dev:res)
        ;;
    esac

    ;;
esac