import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import Components from 'unplugin-vue-components/vite';
import { AntDesignVueResolver } from 'unplugin-vue-components/resolvers';
import * as path from "path";

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
      vue(),
      Components({
        resolvers: [
          AntDesignVueResolver({
            importStyle: false,
          }),
        ],
      }),
  ],
  resolve:{
      alias:{
          '@': path.resolve(__dirname, './src')
      }
  },
  server:{
    host: 'localhost',
    port: 5173,
  },

    // 跨域问题解决
    devServer: {
     port: 8080, // 设置端口号
     https: false, // https:{type:Boolean}配置前缀
     open: true, //配置自动启动浏览器
     proxy: {
      //目的是解决跨域，若测试环境不需要跨域，则不需要进行该配置
      "": {
       // 拦截以 /api 开头的url接口
       target: 'localhost', //目标接口域名
       changeOrigin: true, //是否跨域
       //ws: true, //如果要代理 websockets，配置这个参数
       secure: false, // 如果是https接口，需要配置这个参数
       // pathRewrite: {
       //  // 标识替换
       //  "^/api": "", //重写接口 后台接口指向不统一 所以指向所有/
       // },
      },
     },
    },


})
