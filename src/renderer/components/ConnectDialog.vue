<script setup lang="ts">
import { ElDialog, ElButton, ElInput, ElForm, ElFormItem } from "element-plus";
import { reactive, ref } from 'vue'

export interface ConnInfo {
  host: string,
  port: string,
  db: string,
  user: string,
  pwd: string
}

const conn_info = ref<ConnInfo>(reactive({
  host: '127.0.0.1',
  port: '3306',
  db: 'personnel',
  user: 'root',
  pwd: '2001',
}))

const dialog_visible = ref(false)
const dialog_disable = ref(false)

const message = ref('')

defineProps({
  callback: {
    type: Function,
    default: () => {
    }
  }
})

defineExpose({
  conn_info,
  dialog_visible,
  dialog_disable,
  message
})

</script>

<template>
  <el-dialog style="width: 280px;" v-model:model-value="dialog_visible" :modal="false" header="连接信息">
    <el-form label-width="auto">
      <el-text type="warning"> {{ message }} </el-text>
      <el-form-item label="主机">
        <el-input v-model="conn_info.host" clearable :disabled="dialog_disable" />
      </el-form-item>
      <el-form-item label="端口">
        <el-input v-model="conn_info.port" clearable :disabled="dialog_disable" />
      </el-form-item>
      <el-form-item label="数据库">
        <el-input v-model="conn_info.db" clearable :disabled="dialog_disable" />
      </el-form-item>
      <el-form-item label="用户">
        <el-input v-model="conn_info.user" clearable :disabled="dialog_disable" />
      </el-form-item>
      <el-form-item label="密码">
        <el-input v-model="conn_info.pwd" show-password clearable :disabled="dialog_disable" />
      </el-form-item>
    </el-form>
    <el-button type="primary" @click="() => callback()" :disabled="dialog_disable" style="align-items: end">连接
    </el-button>
  </el-dialog>
</template>

<style scoped></style>