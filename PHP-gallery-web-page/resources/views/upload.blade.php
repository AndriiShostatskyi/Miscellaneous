@extends('layouts.app')

@section('content')

<div class="col-md-10 col-md-offset-3">
    <div class="uploadable">
        <form action="upload" id="upload" method="post" enctype="multipart/form-data">
            <input type="hidden" name="_token" value="{!! csrf_token() !!}">
            <label class="btn btn-default "> 
                Choose <input id="select" type="file" style="display: none;" name="file[]">
            </label>
            <input class="btn btn-default" type='submit' value="Send">
            <p id="message"></p>
            <textarea id="description" style="display:none" type="text" name="description" rows="5" cols="50" required> Enter description of your picture here</textarea> </br>
        </form>
    </div>
</div>
 
<script>

var select =  document.getElementById("select");
var extensionAllowed;

select.addEventListener('change', function(e) {
    extensionAllowed = true;
    if(e.target.files[0].type.split('/').shift() != "image") {
        document.getElementById('message').innerHTML = "Extension of file '"+e.target.files[0].name+"' is not allowed!";
        extensionAllowed = false;
        setTimeout( function() { 
             document.getElementById('message').innerHTML = "";
        }, 2000);
   }
   if(extensionAllowed) { 
       document.getElementById('message').innerHTML = e.target.files[0].name+"<br>";
       document.getElementById('description').style.display = "";
   }
})
 
var request = new XMLHttpRequest();
var form = document.getElementById("upload");

form.addEventListener('submit', function(e) {
    e.preventDefault();
    if(extensionAllowed) {
       var formData = new FormData(form);
       request.open('post', 'upload', false);
       document.getElementById('description').style.display = "none";
       document.getElementById('message').removeChild(document.getElementById('message').childNodes[0]);
       request.addEventListener("load", transferComplete);
       request.send(formData);

       function transferComplete(data) {
           response = JSON.parse(data.currentTarget.response);
           if(response.success){ 
               document.getElementById('message').innerHTML = "File uploaded successfully";
               setTimeout ( function () { 
                  document.getElementById('message').innerHTML = "";
               }, 2000);
            } else {
               document.getElementById('message').innerHTML = "File failed to be uploaded";
            }
       }
    }
 }) 
</script>

@endsection
