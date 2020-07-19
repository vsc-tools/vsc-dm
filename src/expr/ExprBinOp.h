
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * ExprBinOp.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#pragma once

namespace vsc {

enum ExprBinOp {
    BinOp_Eq,
    BinOp_Ne,
    BinOp_Gt,
    BinOp_Ge,
    BinOp_Lt,
    BinOp_Le,
    BinOp_Add,
    BinOp_Sub,
    BinOp_Div,
    BinOp_Mul,
    BinOp_Mod,
    BinOp_And,
    BinOp_Or,
    BinOp_Sll,
    BinOp_Srl,
    BinOp_Xor,
    BinOp_Not,
};

const char *toString(ExprBinOp op);

}

