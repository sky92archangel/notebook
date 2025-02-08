
# 运行方式
#  uvicorn main:app --reload 
#  uvicorn.run("src:app",host="127.0.0.1",port=8000)

#异步上下文控制
from contextlib import asynccontextmanager
@asynccontextmanager    
async def lifespan(app:FastAPI):
    print("server is starting...") #服务器开始前运行
    yield 
    print("server is stopping...") #服务器结束时运行


from fastapi import FastAPI
app = FastAPI(
    title="test service",
    version="0.1.0",
    description="demo",
    lifespan=lifespan
              )


#跨域问题
from fastapi.middleware.cors import CORSMiddleware
origins = [
    'http://0.0.0.0:3000'
]
app.add_middleware(
    CORSMiddleware,
    allow_origins=origins
)

##一般做法
@app.get("/")
async def root ():
    return{"message":"hello"}

##动态路由
@app.get("/user/{username}")
def user_page(username:str):
    return f"the name is {username}"


##body请求
from pydantic import BaseModel
class LoginForm(BaseModel):
    username:str
    password:str
@app.post("/login")
async def login(body:LoginForm):
    username=body.username
    password=body.password
    if username=="admin" and password == '123':
        token = {"status":"login","username":"admin"}
        return token
    else:
        return {"error":"error"}


##分离路由
from fastapi.routing import APIRouter
myrouter=APIRouter()
#127.0.0.1:8000/items/foo
@myrouter.get("/foo")
async def foo():
    return "fooO"
# 127.0.0.1:8000/items/bar?item_id=4
@myrouter.get("/bar")
async def get_item_by_id(item_id:int):
    return "bar"
#最后集中到app路径
app.include_router(router=myrouter,prefix="/items")