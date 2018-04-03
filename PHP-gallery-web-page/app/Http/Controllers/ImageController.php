<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Image;
use Storage;
use App\Http\Requests;
use Validator;

class ImageController extends Controller 
{
    public function __construct() 
    {
        $this->middleware('auth');
    }
    
    protected function upload(Request $request) 
    {
        date_default_timezone_set("Europe/Kiev");
        
        $image = new Image;
        $image->description =  $request->description;
        $image->save();
    
        $id = Image::orderBy('id', 'desc')->first()->id;
        
        $file =  $request->file('file');
        
        switch($file[0]->getMimeType())
        {
            case 'image/jpeg':
                $image = imagecreatefromjpeg($request->file('file')[0]->getPathName());
                break;
                
            case 'image/png':
                $image = imagecreatefrompng($request->file('file')[0]->getPathName());
                break;
                
            case 'image/gif':
                $image = imagecreatefromgif($request->file('file')[0]->getPathName());
                break;
                
            default:
                return \Response::json(array('success' => false));
        }
        
        unlink($request->file('file')[0]->getPathName());
        
        $max_width = 800;
        $max_height = 600;
        $qlt = 500;
        $name = $id.'mini.jpg';
        
        for($i = 2; $i--; $qlt += 225, $max_width += 200, $max_height += 200, $name = $id.'.jpg')
        {
            $old_width      = imagesx($image);
            $old_height     = imagesy($image);
            $scale          = min($max_width/$old_width, $max_height/$old_height);
            $new_width      = ceil($scale*$old_width);
            $new_height     = ceil($scale*$old_height);
            
            $new = imagecreatetruecolor($new_width, $new_height);
            imagecopyresampled($new, $image,  0, 0, 0, 0,  $new_width, $new_height, $old_width, $old_height);
            ob_start();
            imagejpeg($new, NULL, $qlt);
            $data = ob_get_clean();
            imagedestroy($new);
            Storage::put($name, $data);
        }
        
        imagedestroy($image);
        
        return \Response::json(array('success' => true));
    }

}
