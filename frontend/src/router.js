import LoginPage from "@/pages/LoginPage.vue";
import {createRouter,createWebHashHistory} from "vue-router";
import MainPage from "@/pages/MainPage.vue";
import UserTablePage from "@/pages/user/UserTablePage.vue";
import AddUserPage from "@/pages/user/AddUserPage.vue";
import RouterRedirect from "@/pages/RouterRedirect.vue";
import HelloWorld from "@/pages/HelloWorld.vue";

const EmptySlot = {template:'<RouterView/>'}

const routes = [
    {
        path: '/login',
        component: LoginPage
    },
    {
        path: '/page',
        component: MainPage,
        children:[
            {
                path: 'user',
                name: '用户管理',
                component: RouterRedirect,
                redirect: to => {return to.path + '/table'},
                children:[
                    {
                        path: 'table',
                        name: '浏览用户',
                        component: UserTablePage
                    },
                    {
                        path: 'add',
                        name: '创建用户',
                        component: AddUserPage
                    }
                ]
            },
            {
                path: 'book',
                name: '图书管理',
                component: RouterRedirect,
                redirect: to => {return to.path + '/table'},
                children:[
                    {
                        path: 'table',
                        name: '浏览图书',
                        component: HelloWorld
                    }
                ]
            }
        ]
    }





]
export default createRouter({
    history: createWebHashHistory(),
    routes,
})
