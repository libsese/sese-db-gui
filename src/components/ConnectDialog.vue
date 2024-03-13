<template>
  <el-dialog style="width: 300px;" v-model="dialog_visible" :modal="false" header="连接信息" v-loading="disable">
    <el-form label-width="auto">
      <el-form-item label="主机">
        <el-input v-model="conn_info.host" clearable :disabled="disable"/>
      </el-form-item>
      <el-form-item label="端口">
        <el-input v-model.number="conn_info.port" clearable :disabled="disable"/>
      </el-form-item>
      <el-form-item label="数据库">
        <el-input v-model="conn_info.db" clearable :disabled="disable"/>
      </el-form-item>
      <el-form-item label="用户">
        <el-input v-model="conn_info.user" clearable :disabled="disable"/>
      </el-form-item>
      <el-form-item label="密码">
        <el-input v-model="conn_info.pwd" show-password clearable :disabled="disable"/>
      </el-form-item>
    </el-form>
    <el-button type="primary" @click="callback" :disabled="disable" style="align-items: end">连接</el-button>
  </el-dialog>
</template>

<script>
import {defineComponent, reactive, ref} from 'vue';
import {ElDialog, ElButton, ElInput, ElForm, ElFormItem} from "element-plus";

export default defineComponent({
  components: {
    ElDialog,
    ElButton,
    ElInput,
    ElForm,
    ElFormItem
  },
  props: {
    callback: Function
  },
  setup() {
    const conn_info = reactive({
      host: '127.0.0.1',
      port: 3306,
      db: '',
      user: 'root',
      pwd: ''
    })

    const dialog_visible = ref(false)

    const disable = ref(true)

    return {
      conn_info,
      disable,
      dialog_visible
    }
  }
})
</script>

<style scoped>

</style>