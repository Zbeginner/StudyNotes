## Spring boot文件上传下载

### 文件上传

之前用SpringMVC的时候文件上传需要依赖与Apache Commons FilUpload的组件，需要额外导入两个jar包

- commons-fileupload-1.3.2.jar
- commons-io-2.5.jar

版本可以不一样。(别的配置这里就不说了)

但是Springboot内部web依赖spring-boot-starter-web已经为我们处理了这中间的步骤我们直接用MultipartFile实现文件上传功能就可以了。

```java

package org.springframework.web.multipart;

...

public interface MultipartFile extends InputStreamSource {
   ...
}
```

这里就有给小问题了。如果在SpringBoot中，通过Maven或者各种方式你加了commons-fileupload的依赖。就会产生问题。

#### 前端

```html
<body>
    <div class="fileupload">
        <form class="formstyle" action="http://localhost:8080/upload" method="POST" enctype="multipart/form-data">
            <input type="file" name="file" multiple/>
            <input class="butto" type="submit" value="文件上传"/>
        </form>
    </div>
</body>
<style>
    .fileupload{
        height: 400px;
        widows: 100px;
        display: flex;
        justify-content: center;
        align-items: center;
    }
    .formstyle{
        display: flex;
        flex-direction: column;
    }
    .butto{
        margin-top: 20px;
        height: 30px;
        width: 35%;
        float: right;
    }
</style>
```



#### 后端

```java
@PostMapping("/upload")
    public String importRentInfo(MultipartFile file, HttpServletResponse response) throws IOException {

        String filename = file.getOriginalFilename();
        //     存在项目的某个目录下
        String pathName = System.getProperty("user.dir") + "/UploadFile/" + filename ;
        //     存在指定目录下  String pathName="C:/UploadFile/"+filename;
        Path path = Paths.get(pathName);
        //     判断路径是否存在如果不存在则创建对应文件夹
        if (!Files.isWritable(path)) {
            Files.createDirectories(Paths.get(System.getProperty("user.dir") + "/UploadFile"));
        //      Files.createDirectories(Paths.get("C:/LISBackupFile"));
        }
        try {
            Files.write(path, file.getBytes());//将文件存入本地
        }catch (Exception e){
            return "Error";
        }
        return "Success";
    }
```



```java
 /**
  * 多文件
  * @param files
  * @param request
  * @return
  */
@PostMapping("/upload2")
    public String filerUpload(@RequestParam("file") List<MultipartFile> files, HttpServletRequest request){
        if(!files.isEmpty()&&files.size()>0){
            for(MultipartFile file:files){
                String path=request.getServletContext().getRealPath("/upload/");
                File file1=new File(path);
                if(!file1.exists()){
                    file1.mkdir();
                }
                String newFileName= UUID.randomUUID()+"_"+file.getOriginalFilename();
                try {
                    String pathName=path+newFileName;
                    System.out.println(pathName);
//C:\Users\AIERXUAN\AppData\Local\Temp\tomcatdocbase.4260699858668394207.8080\upload\6f85f392-7561-4fee-813f-f73120a87595_2019年大学生创新创业训练计划立项项目结题答辩的通知.docx
//C:\Users\AIERXUAN\AppData\Local\Temp\tomcatdocbase.4260699858668394207.8080\upload\15528784-ae2c-499f-950f-3ea76cf8c511_fileload.html
//通过打印的地址可以看出，上传的文件存在了tomcat的临时目录里。
                    file.transferTo(new File(pathName));
                }catch (Exception e){
                    //e.printStackTrace();
                    return "error";
                }
            }
            return "success";
        }
        return "fault";
    }
```

### 文件下载

#### 前端

```html
<body>
    <a href="http://127.0.0.1:8080/test">文件下载</a>
</body>
```

#### 后端

```java
 /**
  * 下载测试文件
  */
@GetMapping("/test")
public ResponseEntity<InputStream> downloadTestFile(HttpServletRequest request)throws Exception{
        return download(request,"下载测试.txt");
}

public ResponseEntity download(HttpServletRequest request, String filename)throws Exception{
    	//从项目目录下获取要下载的文件
        Resource resource=new ClassPathResource("static/"+filename);
    	//设置请求头
        HttpHeaders headers=new HttpHeaders();
    	//对文件名编码，防止中文文件乱码
        filename=this.getFilename(request,filename);
        headers.setContentDispositionFormData("attachment",filename);
        headers.setContentType(MediaType.parseMediaType("application/force-download"));
        return  ResponseEntity
                .ok()
                .headers(headers)
                .body(new InputStreamResource(resource.getInputStream()));
}
public String getFilename(HttpServletRequest request,String filename)throws Exception{
        String[] IEBrowserKeyWords={"MSIE","Trident","Edge"};
        String userAgent=request.getHeader("User-Agent");
        for(String keyWord:IEBrowserKeyWords){
            if(userAgent.contains(keyWord)){
                return URLEncoder.encode(filename,"UTF-8");
            }
        }
        return new String(filename.getBytes("UTF-8"),"ISO-8859-1");
}
```

