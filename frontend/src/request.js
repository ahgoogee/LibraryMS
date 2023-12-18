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
        else {
            if(router.currentRoute.value.path !== '/login')
                router.push("/login").then()
        }

        return config
    },
    err => {
        return Promise.reject(err)
    }
)

// http response 响应拦截器
instance.interceptors.response.use(
    async response => {
        return await handleData(response);
    },
    error => {

    })

function generateUrl (url) {
    return config.serviceBaseUrl + config.servicePath + url
}

const handleData = async response=>{
    console.log('response:')
    console.log(response)

    if(response.status >= 200 && response.status < 300) return response;

    switch (response.status){
        case 401:
            // 未登录,跳转到登录页
            if(router.currentRoute.value.path !== '/login')
                await router.push("/login")
            break;
    }

    message.error(response.statusText)

    return null;
}

function handleError (error) {
    return error
}

const post = async (url, data) => {
    return instance
        .post(generateUrl(url), data)
        .catch(handleError)
}
const get = async (url, param) => {
    return instance
        .get(generateUrl(url),{
            params:param
        } )
        .catch(handleError)
}


export default {
    post,
    get
}


