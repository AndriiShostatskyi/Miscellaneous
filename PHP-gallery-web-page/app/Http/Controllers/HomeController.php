<?php

namespace App\Http\Controllers;

use App\Http\Requests;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;
use App\Image;
use Illuminate\Pagination\Paginator;
use Illuminate\Pagination\LengthAwarePaginator;
use Illuminate\Database\Eloquent\Model;

class HomeController extends Controller
{
     /*
    public function __construct()
    {
        $this->middleware('auth');
    }
    */

    public function index(Request $request)
    {
        $sortType = $request->input('sort');
        
        switch($sortType)
        {
            case 'date ascending':
                $images = Image::orderBy('created_at', 'asc')->paginate(12);
                break;
                
            case 'views ascending':
                $images = Image::orderBy('views', 'asc')->paginate(12);
                break;
                
            case 'views descending':
                $images = Image::orderBy('views', 'desc')->paginate(12);
                break;
                
            default:
                $images = Image::orderBy('created_at', 'desc')->paginate(12);
                break;
        }
        return view('home', ['images' => $images]);
    }
    
    public function viewsIncr(Request $request)
    {
        Image::where('id', '=', $request->query('id'))->increment('views');
        return redirect()->back();
    }
}


