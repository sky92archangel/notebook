# Haskell

 

sky92@sky92-virtual-machine

sky92@sky92



## 安装

```SHELL
#安装
sudo apt-get install haskell-platform

#检查安装
sky92@sky92:/tmp $ ghci --version
The Glorious Glasgow Haskell Compilation System, version 8.8.4

```



## 使用

```shell
#进入命令行  
sky92@sky92:/tmp $ ghci
GHCi, version 8.8.4: https://www.haskell.org/ghc/  :? for help
Prelude>  

#退出
Ctrl+Z   
```



## 语法基础 

```haskell
Prelude> 1+2
3
Prelude> 1*2
2
Prelude> 1-2
-1
Prelude> 1/2
0.5


Prelude> 1>2
False
Prelude> 2>1
True
Prelude> 1==1
True
Prelude> 2==3
False

--     /=  就是 != 
Prelude> 1/=1
False
Prelude> 2/=1
True

Prelude> not True
False
Prelude> not False
True


--  mod取余数
--  一般是 				func  param1  param2
--  ` 反引号为中缀表达       param1 `func` param2
Prelude> 10 `mod` 5
0
Prelude> mod 10 5
0

Prelude> [1,2,4,5,7]
[1,2,4,5,7]
Prelude> [1,8]++[8,7]++[74,54]
[1,8,8,7,74,54]
Prelude> 3:[8,8,7]
[3,8,8,7]


Prelude> take 2 [3,5,6,7,8,9]
[3,5]
Prelude> drop 2 [3,5,6,7,8,9]
[6,7,8,9]
Prelude> head [3,5,6,7,8,9]
3
Prelude> tail [3,5,6,7,8,9]
[5,6,7,8,9]
Prelude> init [3,5,6,7,8,9]
[3,5,6,7,8]
Prelude> last [3,5,6,7,8,9]
9
Prelude> elem 1 [3,1,5,7,8,11]
True
Prelude> elem 2 [3,1,5,7,8,11]
False
Prelude> 1 `elem` [3,1,5,7,8,11]
True
Prelude> 2 `elem` [3,1,5,7,8,11]
False

-- index取数
Prelude> [131,2334,73,549,95,66,77] !! 0
131
Prelude> [131,2334,73,549,95,66,77] !! 1
2334
Prelude> [131,2334,73,549,95,66,77] !! 2
73

Prelude> [1..4]
[1,2,3,4]
Prelude> [1..23]
[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23]
Prelude> [1,3..23]
[1,3,5,7,9,11,13,15,17,19,21,23]

-- 推导式 类似数学集合解析表达法  | 前是操作   | 后是要求条件
--  x <-[1..10] x取1-10内，  x*2 >= 12  所有x*2大于12的所有x ， x*2 并乘以2返回结果
Prelude> [x*2 | x <-[1..10],x*2 >= 12 ]
[12,14,16,18,20]
-- 
Prelude> [x*2 | x <-[1..10], mod x 2 == 1  ]
[2,6,10,14,18]

-- 无限列表常用于极限运算或者质数获得
Prelude> [1.. ] 
-- x <-[1..] x为自然数 ，mod x 7 == 0  x为7的倍数 或 mod x 10 == 7  个位为7的x
Prelude> take 10 [ x | x <-[1..], mod x 7 == 0 || mod x 10 == 7 ]
[7,14,17,21,27,28,35,37,42,47]


-- 数组为列表 
Prelude> "hello world" !! 3
'l'
Prelude> "hello world" !! 4
'o'
Prelude> "hello world" !! 5
' '
 
```



## 函数定义

```haskell

Prelude> ttt = (*3)
Prelude> ttt 3
9

Prelude> lt_ten = (<10)
Prelude> lt_ten 2
True
Prelude> lt_ten 12
False
 

--- 乘以3函数定义 
Prelude> triple x = 3 * x
Prelude> triple 6
18
Prelude> triple 2
6
Prelude> triple 1
3

-- 向量长度
Prelude> distance x y  = sqrt ( x*x + y*y )
Prelude> distance 3 4
5.0

--  ：}   ：{    控制多行输入   describe 模式匹配  类似switch
Prelude> :{
Prelude| describe "ccd" = "rich"
Prelude| describe "rico" = "poor"
Prelude| describe "1" = "true"
Prelude| describe "0" = "false"
Prelude| describe x = "no info"   -- 无任何匹配
Prelude| :}
 
Prelude> describe "1"
"true"
Prelude> describe "0"
"false"
Prelude> describe "ccd"
"rich"
Prelude> describe "rico"
"poor"


--- 定义范围匹配函数
Prelude> :{
Prelude| myfunc x
Prelude|  | x <= 10 = x
Prelude|  | x <= 20 = x/2
Prelude|  | x <= 30 = x*x
Prelude|  | otherwise = x*x*x
Prelude| :}

Prelude> myfunc 3
3.0
Prelude> myfunc 13
6.5
Prelude> myfunc 23
529.0
Prelude> myfunc 30
900.0
Prelude> myfunc 33
35937.0
Prelude> myfunc 40
64000.0
Prelude> myfunc 43
79507.0


--- 列表判断
Prelude> :{
Prelude| listFunc [] = "Empty"
Prelude| listFunc (x:[]) = "one"
Prelude| listFunc (x:y:[]) = "two"
Prelude| listFunc (x:y:_) = "more than two"
Prelude| :}
Prelude> listFunc [1]
"one"
Prelude> listFunc [1,1]
"two"
Prelude> listFunc [2,1,6]
"more than two"
Prelude> listFunc []
"Empty"

--- 递归   
--单元素最大为自己  多元素拆分为首元素和除了首元素的列表  
--将首元素和后续列表最大元素比较  后续列表最大元素再次由该函数计算决定
--放空列表则出错  应该加上 Prelude| maxIntList [] = 0
Prelude> :{
Prelude| maxIntList [x] = x
Prelude| maxIntList (x:xs) = max x (maxIntList xs)
Prelude| :}
Prelude> max
max         maxBound    maxIntList  maximum
Prelude> maxIntList [1,23,5,512,4,324,15,1]
512
Prelude> maxIntList []
*** Exception: <interactive>:(108,1)-(109,41): Non-exhaustive patterns in function maxIntList

-- 列表递归反转 首元素和剩余列表 将首元素拼接到剩余列表的尾部  并将剩余列表再做同样操作
Prelude> :{
Prelude| reverse [] = []
Prelude| reverse [x] = [x]
Prelude| reverse (x:xs) = reverse xs ++ [x]
Prelude| :}
Prelude> reverse [1,2,3,4,5,6,7]
[7,6,5,4,3,2,1]

-- 排序
Prelude> :{
Prelude| quicksort [] = []
Prelude| quicksort (x:xs) =(quicksort[y|y<-xs,y<=x]++[x]++quicksort[y|y<-xs,y>=x])
Prelude| :}
Prelude> quicksort [41324,142,4124,5,1,61,535,5351,55,333,15,35,135,5,351,5]
[1,5,5,5,15,35,55,61,135,142,333,351,535,4124,5351,41324]

  
```



## curry化函数 类型签名

```haskell

Prelude> distance x y  = sqrt ( x*x + y*y )
Prelude> distance 3 4
5.0
-- 查看函数类型
Prelude> :t distance
distance :: Floating a => a -> a -> a
-- distance :: Floating a => (a -> (a -> (a)))
-- 设distance为函数f0 
-- f0接受a类型的值作为参数，返回函数 f1=(a -> (a)) 
-- f1接受a类型的值作为参数，返回 a 值
-- a 符合 Floating
-- 即所有函数都只传入一个参数  参数可以是函数也可以是值



```



## 内置高阶函数

```haskell

-- 列表应用 map
Prelude> map (*3) [1,2,3,4]
[3,6,9,12]

-- 条件规律 filter
Prelude> filter (<10) [1,24,2,3,1,22,2]
[1,2,3,1,2]

--  foldl
-- Haskell的lambda写法 (\参数1 参数2 -> 操作) 默认值 操作目标   
--  这里就是 列表累加   (((0)+1)+24)+2...
Prelude> foldl (\acc x -> acc + x) 0 [1,24,2,3,1,22,2]
55
-- 简化写法
Prelude> foldl (+) 0 [1,24,2,3,1,22,2]
55

```



## Haskell 类型类 functor   Applicative  与 monad

```haskell

------------------------------ Functor 函子  ----------------------------------
-- 一个打包的值 进入函数解包后运算 得到结果后再次打包输出
Prelude> :i Functor
class Functor (f :: * -> *) where
  fmap :: (a -> b) -> f a -> f b
  (<$) :: a -> f b -> f a
  {-# MINIMAL fmap #-}
        -- Defined in ‘GHC.Base’
instance Functor (Either a) -- Defined in ‘Data.Either’
instance Functor [] -- Defined in ‘GHC.Base’
instance Functor Maybe -- Defined in ‘GHC.Base’
instance Functor IO -- Defined in ‘GHC.Base’
instance Functor ((->) r) -- Defined in ‘GHC.Base’
instance Functor ((,) a) -- Defined in ‘GHC.Base’

-- Functor 为数据环境 fmap 去改变Functor数据环境  得到结果
-- 将包装的数据 传入函数 
Prelude> fmap (+3) [3]
[6]
Prelude> fmap (+3) []
[]
Prelude> fmap (+3) Nothing
Nothing

-- 将一个值放入双参数函数  则 值会填充第一个参数位并返回一个函数
Prelude> fmap (+) (Just 3) 
<interactive>:192:1: error:
    • No instance for (Show (Integer -> Integer))
        arising from a use of ‘print’
        (maybe you haven't applied a function to enough arguments?)
    • In a stmt of an interactive GHCi command: print it

---------------------------------    Applicative   ---------------------------------
-- Applicative获得一个包装了的函数 以及一个 包装了的值  两者拿出来运算  得到结果再次打包输出
Prelude> :i Applicative
class Functor f => Applicative (f :: * -> *) where
  pure :: a -> f a
  (<*>) :: f (a -> b) -> f a -> f b
  GHC.Base.liftA2 :: (a -> b -> c) -> f a -> f b -> f c
  (*>) :: f a -> f b -> f b
  (<*) :: f a -> f b -> f a
  {-# MINIMAL pure, ((<*>) | liftA2) #-}
        -- Defined in ‘GHC.Base’
instance Applicative (Either e) -- Defined in ‘Data.Either’
instance Applicative [] -- Defined in ‘GHC.Base’
instance Applicative Maybe -- Defined in ‘GHC.Base’
instance Applicative IO -- Defined in ‘GHC.Base’
instance Applicative ((->) a) -- Defined in ‘GHC.Base’
instance Monoid a => Applicative ((,) a) -- Defined in ‘GHC.Base’
-- 实例
Prelude> Just (+3) <*> Just 1
Just 4
Prelude> [(+1),(*2)] <*> [2,6]
[3,7,4,12]




-- monad类型是Applicative的升级版  
-- 输入monad值 得到经过函数处理后的 输出monad值
Prelude> :i Monad
class Applicative m => Monad (m :: * -> *) where
  (>>=) :: m a -> (a -> m b) -> m b
  (>>) :: m a -> m b -> m b
  return :: a -> m a
  {-# MINIMAL (>>=) #-}
        -- Defined in ‘GHC.Base’
instance Monad (Either e) -- Defined in ‘Data.Either’
instance Monad [] -- Defined in ‘GHC.Base’
instance Monad Maybe -- Defined in ‘GHC.Base’
instance Monad IO -- Defined in ‘GHC.Base’
instance Monad ((->) r) -- Defined in ‘GHC.Base’
instance Monoid a => Monad ((,) a) -- Defined in ‘GHC.Base’
-- 定义函数half  
Prelude> :{
Prelude| half x = if even x
Prelude|     then Just (x `div` 2)
Prelude|     else Nothing
Prelude| :}
-- 将带有数据的monad函数传入 half函数  
-- half函数能够 解包Just得到数据  并对数据操作 得到结果 再次打包输出 
Prelude> Just 20 >>= half
Just 10   
Prelude> Just 20 >>= half >>=half
Just 5
Prelude> Just 20 >>= half >>=half >>= half
Nothing
-- 如此可以使用 数据 => 函数=> 函数=> 函数=> 函数 = 结果 的链式调用 

Prelude> Just  1 >>= \x -> Just(x+3)
Just 4

```



###  原理和应用

```haskell
-- 数据 => 函数=> 函数=> 函数=> 函数 = 结果 的链式调用
-- 类似于MVVM的改变VM状态   VM状态   界面的变化进入dispatcher去改变VM内的数据
 
 
--读取文件
-- getLine >== readFile >== putStrLn


 
```































