import LoginPage from "@/pages/LoginPage.vue";
import {createRouter,createWebHashHistory} from "vue-router";
import MainPage from "@/pages/MainPage.vue";
import UserTablePage from "@/pages/user/UserTablePage.vue";
import AddUserPage from "@/pages/user/AddUserPage.vue";
import RouterRedirect from "@/pages/RouterRedirect.vue";
import HelloWorld from "@/pages/HelloWorld.vue";
import AdminTablePage from "@/pages/admin/AdminTablePage.vue";
import AddAdminPage from "@/pages/admin/AddAdminPage.vue";
import TypeTablePage from "@/pages/type/TypeTablePage.vue";
import AddTypePage from "@/pages/type/AddTypePage.vue";
import BookTablePage from "@/pages/book/BookTablePage.vue";
import AddBookPage from "@/pages/book/AddBookPage.vue";
import RecordTablePage from "@/pages/record/RecordTablePage.vue";
import RegisterPage from "@/pages/RegisterPage.vue";

const routes = [
    {
        path: '/login',
        component: LoginPage
    },
    {
        path: '/register',
        component:RegisterPage
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
                path: 'admin',
                name: '管理员管理',
                component: RouterRedirect,
                redirect: to => {return to.path + '/table'},
                children:[
                    {
                        path: 'table',
                        name: '浏览管理员',
                        component: AdminTablePage
                    },
                    {
                        path: 'add',
                        name: '创建管理员',
                        component: AddAdminPage
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
                        component: BookTablePage
                    },
                    {
                        path: 'add',
                        name: '创建图书',
                        component: AddBookPage
                    }
                ]
            },
            {
                path: 'type',
                name: '图书类别管理',
                component: RouterRedirect,
                redirect: to => {return to.path + '/table'},
                children:[
                    {
                        path: 'table',
                        name: '浏览图书类别',
                        component: TypeTablePage
                    },
                    {
                        path: 'add',
                        name: '创建图书类别',
                        component: AddTypePage
                    }
                ]
            },
            {
                path: 'record',
                name: '借阅管理',
                component: RouterRedirect,
                redirect: to => {return to.path + '/table'},
                children:[
                    {
                        path: 'table',
                        name: '浏览借阅记录',
                        component: RecordTablePage
                    }
                ]
            },
        ]
    }





]
export default createRouter({
    history: createWebHashHistory(),
    routes,
})
