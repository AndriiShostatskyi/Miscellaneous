<?php

Route::auth();

Route::get('upload', 'AdminController@upload');

Route::post('upload', 'ImageController@upload');

Route::get('admin', 'AdminController@index');

Route::get('delete', 'AdminController@delete');

Route::post('changeDesc/{id}', 'AdminController@changeDesc');

Route::get('home', 'HomeController@index');
Route::post('home', 'HomeController@index');

Route::get('/', function(){
      return redirect('home');
});

Route::get('viewsIncr', 'HomeController@viewsIncr');

Route::post('sorting', 'HomeController@sorting');


