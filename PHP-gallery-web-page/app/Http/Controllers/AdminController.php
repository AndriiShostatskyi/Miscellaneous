<?php
namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Image;
use App\Http\Requests;
use Storage;

class AdminController extends Controller
{
    public function __construct() 
    {
        $this->middleware('auth');
    }
    
    protected function index()
    {
        $images = Image::orderBy('created_at', 'desc')->paginate(12);
        return view('admin', ['images' => $images]);
    }
    
    protected function upload()
    {
         return view('upload');
    }
    
    protected function delete(Request $request)
    {
        Storage::delete($request->query('id').".jpg");
        Storage::delete($request->query('id')."mini.jpg");
        Image::where('id', '=', $request->query('id'))->delete();
        
        return \Response::json(array('success' => true));
    }
    
    protected function changeDesc($id, Request $request)
    { 
         Image::where('id', '=', $id)->update(['description'=>$request->input('description')]);
         return redirect()->back();
    }
    
}
