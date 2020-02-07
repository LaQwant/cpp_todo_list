echo ' -> Ceci est une batterie de tests pour le programme de gestion de todo-list. La commande est affichée, puis son action est réalisée.'
echo ">>> ./cpp_todo_app list"
./cpp_todo_app list
echo '>>> ./cpp_todo_app create -t "Ma première tâche !" -d "Ceci est une description" -b 01/01/2020 -e 02/03/2020 --progress 50'
./cpp_todo_app create -t "Ma première tâche !" -d "Ceci est une description" -b 01/01/2020 -e 02/03/2020 --progress 50
echo '>>> ./cpp_todo_app create -t "Une sous-tâche" --progress 50 -m 1 -e 02/03/2020'
./cpp_todo_app create -t "Une sous-tâche" --progress 50 -m 1 -e 02/03/2020
echo '>>> ./cpp_todo_app create -t "Une autre sous-tâche" --progress 50 -m 1'
./cpp_todo_app create -t "Une autre sous-tâche" --progress 50 -m 1
echo '>>> ./cpp_todo_app create -t "Une sous-sous-tâche" -d "Je suis une autre description" -m 1.1'
./cpp_todo_app create -t "Une sous-sous-tâche" -d "Je suis une autre description" -m 1.1
echo '>>> ./cpp_todo_app create --title UneTacheEnUnLongMot --priority "high"'
./cpp_todo_app create --title UneTacheEnUnLongMot --priority "high"
echo '>>> ./cpp_todo_app list'
./cpp_todo_app list
echo '>>> ./cpp_todo_app list -m 1'
./cpp_todo_app list -m 1
echo '>>> ./cpp_todo_app edit 1 -d "Ceci est la nouvelle description" --priority low'
./cpp_todo_app edit 1 -d "Ceci est la nouvelle description" --priority low
echo '>>> ./cpp_todo_app show 1'
./cpp_todo_app show 1
echo '>>> ./cpp_todo_app del 1.1'
./cpp_todo_app del 1.1
echo '>>> ./cpp_todo_app del 1.1'
./cpp_todo_app del 1.1
echo '>>> list ./cpp_todo_app list'
./cpp_todo_app list
echo '>>> ./cpp_todo_app comment 1 "Ceci est un commentaire sur la tâche 1"'
./cpp_todo_app comment 1 "Ceci est un commentaire sur la tâche 1"
echo '>>> ./cpp_todo_app comment 1 "Ceci est un deuxième commentaire sur la tâche 1"'
./cpp_todo_app comment 1 "Ceci est un deuxième commentaire sur la tâche 1"
echo '>>> ./cpp_todo_app show 1'
./cpp_todo_app show 1
echo ' -> Et maintenant, on teste quelques commandes erronées'
echo '>>> ./cpp_todo_app commande_qui_n_existe_pas'
./cpp_todo_app commande_qui_n_existe_pas
echo '>>> ./cpp_todo_app create'
./cpp_todo_app create
echo '>>> ./cpp_todo_app create -t titre --attribut_inconnu bonjour'
./cpp_todo_app create -t titre --attribut_inconnu bonjour
echo '>>> ./cpp_todo_app create -t'
./cpp_todo_app create -t
echo ' -> Et maintenant, on lance la commande "./cpp_todo_app" pour passer en mode ligne de commande (rentrez les commandes que vous voulez pour tester).'
./cpp_todo_app
