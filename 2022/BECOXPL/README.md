# Mini Treinamento Mobile Exploitation

Este arquivo tem por objetivo catalogar os comandos utilizados durante o treinamento

## Copyright

Arquivo pertencente ao treinamento de Hacking Mobile Application
Autor: Sec4US - Hélvio Junior (M4v3r1ck)

**Proibida a reprodução ou publicação deste material sem prévia autorização expressa**

## Live

Este mini treinamento foi realizado em 29/07/2022 em uma live para o Sexta Hack do beco do Exploit

Segue o link da live no Youtube: https://www.youtube.com/watch?v=9MM9Gphe0IY

## Listando devices

### Hello World
```bash
adb devices
```

## Instalando apk

### Hello World
```bash
adb install app.apk
```

## Disassembly

### APKTool

**Disassembly**
```bash
apktool d app.apk –o output
```

### Enjarify

**Instalando Enjarify**
```bash
git clone https://github.com/Storyyeller/enjarify.git /opt/enjarify
chmod 777 /opt/enjarify/enjarify.sh
ln -s /opt/enjarify/enjarify.sh /usr/local/bin/enjarify
```

**Executando Enjarify**
```bash
enjarify app.apk –o app.jar
```

### MobSF
```bash
git clone https://github.com/MobSF/Mobile-Security-Framework-MobSF
mv Mobile-Security-Framework-MobSF/ MobSF
cd MobSF/
./setup.sh
./run.sh
```


## Frida

### Resgatando ABI
```bash
adb shell getprop ro.product.cpu.abi
```

#### Envia o binário do frida server para o Android 
```bash
adb push frida-server /data/local/tmp/frida-server
```

#### Inicia o adb como root

**Opção 1: Comumente utilizada em emulador**
```bash
adb root
```

**Opção 2: Comumente utilizada em dispositivo físico**
`adb shell` e posteriormente `su`

#### Altera a permissão de execução do frida no Android 

**Opção 1: Comumente utilizada em emulador (estando o adb como root)**
```bash
adb shell chmod 755 /data/local/tmp/frida-server
```

**Opção 2: Em dispositivo físico (onde é necessário executar su)**
```bash
adb shell su –c chmod 755 /data/local/tmp/frida-server
```
ou
```bash
adb shell su 0 chmod 755 /data/local/tmp/frida-server
```

#### Inicia o servidor frida como root
**Opção 1: Comumente utilizada em emulador (estando o adb como root)**
```bash
adb shell /data/local/tmp/frida-server &
```

**Opção 2: Em dispositivo físico (onde é necessário executar su)**
```bash
adb shell su –c /data/local/tmp/frida-server &
```
ou 
```bash
adb shell su 0 /data/local/tmp/frida-server &
```

### Instalando o pacote frida-tools com o python 3 no cliente
```bash
pip3 install frida-tools ou python3 –m pip install frida-tools
```

### Testes de instalação e comunicação entre o cliente frida e o servidor frida

```bash
frida-ps -U
```

### Executando script frida
```bash
frida -U -f <package_nane> -l <script_name> --no-pause
```

### Script Frida


**Criando um script para hook**

```javascript
Java.perform(function () {

  var MainActivity = Java.use("br.com.mobileexploitation.a002flow.MainActivity");
  var onCreate = MainActivity.onCreate.overload('android.os.Bundle');
  onCreate.implemention = function(arg0){
    console.log('onCreate called');
    onCreate.call(this, arg0);
  }

});
```


## Criando variáveis

**java.lang.Boolean**
```javascript
var b1 = Java.use("java.lang.Boolean").$new("True");
var b1 = Java.use("java.lang.Boolean").$new("False");
```

**Boolean primitivo**
```javascript
var b1 = Java.use("java.lang.Boolean").$new("True").booleanValue();
var b1 = Java.use("java.lang.Boolean").$new("False").booleanValue();
```

**String**
```javascript
var s1 = Java.use("java.lang.String").$new("Minha String");
```

## Reflection

**Criando instancia da classe**
```javascript
var ClasseExemplo = Java.use("packane_name.ClasseExemplo");
var exInstance = ClasseExemplo.$new();
```

**Definindo valor em uma variável pública**
```javascript
var ClasseExemplo = Java.use("packane_name.ClasseExemplo");
var exInstance = ClasseExemplo.$new();

var str = Java.use("java.lang.String").$new("Teste OK!");

var mData2 = ClasseExemplo.class.getDeclaredField("mData2");
mData2.set(exInstance, str);
```

**Definindo valor em uma variável privada**
```javascript
var ClasseExemplo = Java.use("packane_name.ClasseExemplo");
var exInstance = ClasseExemplo.$new();

var str = Java.use("java.lang.String").$new("Teste OK!");

var mData1 = ClasseExemplo.class.getDeclaredField("mData1");
mData1.setAccessible(true);
mData1.set(exInstance, str);
```


**Definindo valor em uma variável estática**
```javascript
var ClasseExemplo = Java.use("packane_name.ClasseExemplo");

var str = Java.use("java.lang.String").$new("Teste OK!");

var mData3 = ClasseExemplo.class.getDeclaredField("mData3");
mData3.set(null, str);
```


## SSL/TLS Pinning

### Exemplo código OKHTTP

```java
CertificatePinner certPinner = new CertificatePinner.Builder()
      .add("*.mobilehacking.com.br",
        "sha256/HpwVIsSgIhldMYUpiE6/mpBE9A/zAUHATLhWim7WABQ=")
      .build();

OkHttpClient client = new OkHttpClient.Builder()
        .certificatePinner(certificatePinner)
        .build();

Request request = new Request.Builder()
        .url("https://api1.mobilehacking.com.br/api/v1/generic/")
        .build();
```

## Scripts criados na Live

### App 002 - Bypass Flow control

```java
/*  
    Arquivo pertencente ao treinamento de Hacking Mobile Application
    Autor: Sec4US - Hélvio Junior (M4v3r1ck)

    ** Proibida a reprodução ou publicação deste material sem prévia autorização expressa

    Execute com:
    frida -U -f br.com.mobileexploitation.a002flow -l mob_002_flow.js --no-pause
*/

Java.perform(function(){
    console.log('');
    console.log('======');
    console.log('[#] Treinamento Mobile Hacking Application - Android [#]');
    console.log('======');

    var MainActivity = Java.use("br.com.mobileexploitation.a002flow.MainActivity");
    var onCreate = MainActivity.onCreate.overload('android.os.Bundle');
    onCreate.implementation = function(b1)
    {
        console.log("Hook em MainActivity.onCreate");

        var mRedir = Java.use("java.lang.Boolean").$new("True");
        var redirectActivity = MainActivity.class.getDeclaredField("redirectActivity");
        redirectActivity.set(this, mRedir);

        return onCreate.call(this, b1);
    }


});

```

### App 010 - Bypass Root Detection

```java
/*  
    Arquivo pertencente ao treinamento de Hacking Mobile Application
    Autor: Sec4US - Hélvio Junior (M4v3r1ck)

    ** Proibida a reprodução ou publicação deste material sem prévia autorização expressa

    Execute com:
    frida -U -f br.com.mobileexploitation.app010_rootbeer -l mob_010_rootbeer.js --no-pause
*/

Java.perform(function(){
    console.log('');
    console.log('======');
    console.log('[#] Treinamento Mobile Hacking Application - Android [#]');
    console.log('======');


    var RootBeer = Java.use("com.scottyab.rootbeer.RootBeer");
    var isRooted = RootBeer.isRooted.overload();
    isRooted.implementation = function()
    {
        console.log("Desabilitando RootBeer");

        var b1 = Java.use("java.lang.Boolean").$new("False").booleanValue();

        return b1;
    }


});
```


### App 007 - Bypass TLS Pinning

```java
/*  
    Arquivo pertencente ao treinamento de Hacking Mobile Application
    Autor: Sec4US - Hélvio Junior (M4v3r1ck)

    ** Proibida a reprodução ou publicação deste material sem prévia autorização expressa

    Execute com:
    frida -U -f br.com.mobileexploitation.app007_pinning -l mob_007_pinning.js --no-pause
*/

Java.perform(function(){
    console.log('');
    console.log('======');
    console.log('[#] Treinamento Mobile Hacking Application - Android [#]');
    console.log('======');

    var Pinner = Java.use("okhttp3.CertificatePinner$Builder");
    var add = Pinner.add.overload('java.lang.String', '[Ljava.lang.String;');
    add.implementation = function(a, b)
    {
        console.log("Desabilitando pinagem para " + a);

        return add.call(this,'none',b);
    }


    //Trust Manager (Copiado do frida_multiple_unpinning)
    var X509TrustManager = Java.use('javax.net.ssl.X509TrustManager');
    var SSLContext = Java.use('javax.net.ssl.SSLContext');

    // TrustManager (Android < 7) //
    ////////////////////////////////
    var TrustManager = Java.registerClass({
        // Implement a custom TrustManager
        name: 'dev.asd.test.TrustManager',
        implements: [X509TrustManager],
        methods: {
            checkClientTrusted: function(chain, authType) {},
            checkServerTrusted: function(chain, authType) {},
            getAcceptedIssuers: function() {return []; }
        }
    });
    // Prepare the TrustManager array to pass to SSLContext.init()
    var TrustManagers = [TrustManager.$new()];
    // Get a handle on the init() on the SSLContext class
    var SSLContext_init = SSLContext.init.overload(
        '[Ljavax.net.ssl.KeyManager;', '[Ljavax.net.ssl.TrustManager;', 'java.security.SecureRandom');
    try {
        // Override the init method, specifying the custom TrustManager
        SSLContext_init.implementation = function(keyManager, trustManager, secureRandom) {
            console.log('[+] Bypassing Trustmanager (Android < 7) pinner');
            SSLContext_init.call(this, keyManager, TrustManagers, secureRandom);
        };
    } catch (err) {
        console.log('[-] TrustManager (Android < 7) pinner not found');
        //console.log(err);
    }
});

```

