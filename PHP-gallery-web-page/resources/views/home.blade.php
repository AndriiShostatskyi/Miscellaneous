@extends('layouts.app')

@section('content')
<style>
    
    .animate-bottom {
  position: relative;
  -webkit-animation-name: animatebottom;
  -webkit-animation-duration: 1s;
  animation-name: animatebottom;
  animation-duration: 1s
}

@-webkit-keyframes animatebottom {
  from { bottom:-100px; opacity:0 } 
  to { bottom:0px; opacity:1 }
}

@keyframes animatebottom { 
  from{ bottom:-100px; opacity:0 } 
  to{ bottom:0; opacity:1 }
}
</style>
<div class="animate-bottom">
<div class="container">
    <div class="col-md-10 col-md-offset-1">
        <form class="sort" action="home"  method="POST">    
             <label for="sort"> Sort by criterion </label> 
             <select id ="sort" class="btn btn-default" name="sort">
                  <option> date ascending </option>
                  <option> views ascending </option>
                  <option> views descending </option>
             </select> 
             <input type="submit" class="btn btn-default" type='submit' value="Sort"> 
             <input type="hidden" name="_token" value="{!! csrf_token() !!}">
        </form>
        
    <!-- Gallary -->
    <div class="row">
        <?php $i = 1;?>
        @foreach ($images as $image)
            <div class="column">
                <a href="" class="thumbnail" data-toggle="modal" data-target="#{{$image->id}}">
                    <img src="../../storage/app/{{$image->id}}mini.jpg" alt="{{$image->description}}" 
                    style="width:250px;height:150px" onclick="viewsIncr({{$image->id}})">
                </a>
            </div>
        @endforeach
    </div>
    <div style="text-align:center">
        {!! $images->render() !!}
    </div>
    
    <!-- Modal -->
    @foreach ($images as $image)
    <div class="modal fade" id="{{$image->id}}" role="dialog">
        <div class="modal-dialog modal-md">
            <div class="modal-content">
                <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal">&times;</button>
                <h4 class="modal-title">{{$image->description}}</h4>
                </div>
                <img src="../../storage/app/{{$image->id}}.jpg" alt="{{$image->description}}" style="width:598px;">
            </div>
        </div>
    </div>
    @endforeach
    
   </div>
</div>
</div>
<script>
function viewsIncr(id) {
    var request = new XMLHttpRequest();
    request.open('get', 'viewsIncr?id='+id, false);
    request.send();
}
</script>

@endsection
