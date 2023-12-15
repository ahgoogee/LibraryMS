import axios from 'axios'
import cache from '@/common/cache.js'
import { message } from 'ant-design-vue'
import config from '@/config.js'
import router from "@/router.js";

const instance = axios.create({
    // baseURL 将自动加在 url`前面，除非 url 是一个绝对 URL。
    // 它可以通过设置一个 baseURL 便于为 axios 实例的方法传递相对 URL
    baseURL: config.serviceBaseUrl,
    // timeout设置一个请求超时时间，如果请求时间超过了timeout，请求将被中断，单位为毫秒（ms）
    timeout: 60000,
    // headers是被发送的自定义请求头，请求头内容需要根据后端要求去设置，这里我们使用本项目请求头。
    headers: {
        'Accept': 'application/json',
        'Content-Type': 'application/json'
    }
})

// http request 请求拦截器
instance.interceptors.request.use(
    config => {
        let token = cache.getCache("Token")
        if(token){
            config.headers.set("Token",token)
        }

        return config
    },
    err => {
        return Promise.reject(err)
    }
)

// http response 响应拦截器
instance.interceptors.response.use(
    response => {
        handleData(response.data)
        return response;
    },
    error => {

    })

function generateUrl (url) {
    return config.serviceBaseUrl + config.servicePath + url
}

const handleData = result=>{
    if(result.code === 200) {
        console.log(`response:${result}`)
        return;
    }

    switch (result.code){
        case 501:
        case 502:
            // 未登录,跳转到登录页
            router.push("/login").then()
            break;
    }

}

function handleError (error) {
    return error
}

const post = (url, data) => {
    return instance
        .post(generateUrl(url), data)
        .catch(handleError)
}



export default {
    post
}


