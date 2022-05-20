/**
 * 
 */
package org.crsa.member;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.cookie.Cookie;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.HTTP;

/**
 * @author wengkai
 *
 */
public class AddressM {

	/**
	 * @param args
	 * @throws IOException 
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception, IOException {
		if ( args.length == 0 ) {
			System.out.println("AddressM <n> <date: yyyy mm dd>");
			System.out.println("\t1: 地址");
			System.out.println("\t2: 考试");
			System.out.println("\t3: 补刊");
			return;
		}
		
		DefaultHttpClient httpclient = new DefaultHttpClient();

        HttpGet httpget = new HttpGet("http://www.somewhere.org/admin/");

        HttpResponse response;
        HttpEntity entity;
        List<Cookie> cookies;


        HttpPost httpost = new HttpPost("http://www.somewhere.org/admin/checklogin.php");

        List<NameValuePair> nvps = new ArrayList <NameValuePair>();
        nvps.add(new BasicNameValuePair("name", "kkk"));
        nvps.add(new BasicNameValuePair("pwd", "lalala"));

        httpost.setEntity(new UrlEncodedFormEntity(nvps, HTTP.UTF_8));

        response = httpclient.execute(httpost);
        entity = response.getEntity();

        //System.out.println("Login form get: " + response.getStatusLine());
        if (entity != null) {
        	//entity = response.getEntity();
            BufferedReader in = new BufferedReader(new InputStreamReader(entity.getContent(),Charset.forName("UTF-8")));
            /*String line;
            while ((line=in.readLine())!= null ) {
            	//System.out.println(line);
            }*/
            in.close();
            //entity.consumeContent();
        }

        //System.out.println("Post logon cookies:");
        cookies = httpclient.getCookieStore().getCookies();
        if (cookies.isEmpty()) {
            //System.out.println("None");
        } else {
            for (int i = 0; i < cookies.size(); i++) {
                //System.out.println("- " + cookies.get(i).toString());
            }
        }
        switch ( Integer.parseInt(args[0]) ) { 
        	case 1: 
        		System.out.println("会员证号	会员姓名	会员呼号	原地址	新地址	邮政编码	联系电话	身份证号	申请时间");
        		break;
        	case 2:
        		System.out.println("会员证号	会员姓名	会员呼号	地址	邮政编码	电话	身份证	操作级别	考试级别	考试场地	申请时间");
        		break;
        	case 3:
        		System.out.println("会员证号	会员姓名	会员呼号	地址	邮政编码	刊补	申请时间");
        		break;
        }
        Calendar end = Calendar.getInstance();
        end.add(Calendar.DAY_OF_YEAR, 1);
        Calendar date = Calendar.getInstance();
        //date.set(2009, 7, 11);
        date.set(Integer.parseInt(args[1]),Integer.parseInt(args[2])-1,Integer.parseInt(args[3]));
        for ( ; date.before(end); date.add(Calendar.DAY_OF_YEAR, 1) ) {
        	String ds = String.format("%4d-%02d-%02d", date.get(Calendar.YEAR),
	        		date.get(Calendar.MONTH)+1,
	        		date.get(Calendar.DAY_OF_MONTH));
        	int pg=1;
        	int cnt;
        	do {
        		cnt=0;
        		switch (Integer.parseInt(args[0])) {
        		case 1:
        			httpget = new HttpGet("http://www.somewhere.org/admin/member/member_excel.php?act=excel&page="+
        				pg+"&findtime="+ds+"&findmembername=");
        			break;
        		case 2:
        			httpget = new HttpGet("http://www.somewhere.org/admin/ks/kb_excel.php?act=excel&page="+
        				pg+"&findtime="+ds+"&findmembername=");	
        			break;
        		case 3:
        			httpget = new HttpGet("http://www.crsa.org.cn/admin/kb/kb_excel.php?act=excel&page="+
            			pg+"&findtime="+ds+"&findmembername=");
        		}
            	pg++;
		        response = httpclient.execute(httpget);
		        entity = response.getEntity();
		        if (entity != null) {
		        	BufferedReader in = new BufferedReader(new InputStreamReader(entity.getContent()));
		            String line = in.readLine();
		            while ((line=in.readLine())!= null ) {
		            	cnt++;
		            	System.out.println(line);
		            }
		            in.close();
		        }
        	} while ( cnt>0 );
        }
	}

}
