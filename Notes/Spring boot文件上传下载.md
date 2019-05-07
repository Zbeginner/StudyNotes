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
 /**
  * 直接上多文件，单文件的处理也差不多
  * @param files
  * @param request
  * @return
  */
@PostMapping("/upload")
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

