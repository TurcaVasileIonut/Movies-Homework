# Movies-Homework

A project from college where I learned to apply oop principles and write code that is easy to scale and maintain. 

The project uses Qt 6.3.0 for the graphical user interface
![plot](./screenshots/admin_page.png)


You can add a new movie to the list very easily.
![plot](./screenshots/add_movie.png)

If the movie parameters are valid, the movie is added.
![plot](./screenshots/movie_successfully_added.png)

If the movie parameters are not valid, the movie is not added and an error form is displayed
![plot](./screenshots/invalid_movie_error.png)

You can change an existing movie. The movie will change only if there is a movie with the old parameters and the new set of parameters are suitable for a movie
![plot](./screenshots/change_movie_tab.png)

You can delete a movie. If the chosen movie does not appear in the list, there will be a message form that will inform the user that there is no movie with chosen parameters.
![plot](./screenshots/delete_movie_tab.png)

You can undo each action that modified the list (until you get the list from opening the app)
![plot](./screenshots/undo.png) 

You can filter the displayed movies from the right list by title or by year.
![plot](./screenshots/filter_movies.png)

You can see the movie list sorted by title or by the actor or by year+gen
![plot](./screenshots/sort_movies.png)

You can create a cart and add a chosen by title movie (like a shopping cart)
![plot](./screenshots/add_movie_in_cart.png)
You can also add random movies. You can export the cart content in an external file.
![plot](./screenshots/add_random_number_of_movies_in_cart.png)

You can "draw the cart". The draw cart will open a new window each time it is pressed. 
All windows are updated with each action on the cart in an efficient way.
![plot](./screenshots/draw_cart.png)
![plot](./screenshots/every_number_of_draw.png)
![plot](./screenshots/every_cart_tab_updated.png)
