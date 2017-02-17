from django.shortcuts import render
from datetime import datetime
# Create your views here.
from django.http import HttpResponse
from .models import Post# import class Post from models.py
def hello_world(request):
    #return HttpResponse("hello world")
    return render(request,'hello.html',{
            'current_time':str(datetime.now()),
            })
def home(request):
    post_list=Post.objects.all()
    return render(request,'home.html',{
            'post_list':post_list,
            })
