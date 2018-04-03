@extends('layouts.app')

@section('content')
<div class="container">
    <div class="col-md-8 col-md-offset-1">
        <div class="table-responsive">
            <?php $i = 1;?>
            <table class="table">
                @foreach ($images as $image)
                <tr id="{{$image->id}}">
                    <td><img src="../../storage/app/{{$image->id}}mini.jpg" alt="{{$image->description}}"></td> 
                    <td>
                        <h4> Picture-id: {{$image->id}}</h4>
                        <h4> Description:</h4> 
                        <p>
                            <a id="{{$image->id}}" data-toggle="collapse" data-parent="#accordion" href="#collapse{{$image->id}}">{{$image->description}} </a> 
                            <div id="collapse{{$image->id}}" class="panel-collapse collapse">
                               <form action="changeDesc/{{{$image->id}}}" id="form{{$image->id}}" method="post">
                                   <textarea type="text" name="description"  rows="5" cols="30"> {{$image->description}}</textarea></br>
                                       <input type="hidden" name="_token" value="{!! csrf_token() !!}">
                                       <button type="submit" onclick=changeDesc({{$image->id}});> Change </button> 
                                </form> 
                            </div>
                        </p>
                        <button  type="submit" class="btn btn-info btn-sm" onclick=deleteImg({{$image->id}})> Delete</button> 
                    </td> 
                </tr>
                @endforeach
            </table>
        </div>
        <div style="text-align:center">
            {!! $images->render() !!}
        </div>
    </div>
</div>

<script>

function deleteImg(id) {
   var cnf = confirm("Are you sure you want to delete picture with id "+id);
   
   if(cnf) {
       var request = new XMLHttpRequest();
       request.open('get', 'delete?id='+id, false);
       request.addEventListener("load", transferComplete);
       request.send();
       
        function transferComplete(data) {
        response = JSON.parse(data.currentTarget.response);
        if(response.success){
            alert("Success!");
            $('#'+id).remove();
        } else alert("Error!");
      }
   }
}
</script>

@endsection
